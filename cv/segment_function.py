import cv2
import numpy as np
from sklearn.mixture import GaussianMixture
from scipy.stats import norm
import matplotlib.pyplot as plt
from time import time
import os
from itertools import combinations
from PIL import Image
from itertools import combinations, permutations
# from shapely.geometry import Polygon, Point

def load_image(path, max_height=700):
    img = cv2.imread(path)
    h, w = img.shape[:2]
    if h > max_height:
        img = cv2.resize(img, (max_height*w//h, max_height))
    return img, h, w

def get_convex_hull(img):
    img = img.copy()

    n, labels, stats, centroids = cv2.connectedComponentsWithStats(img)
    if n == 1:
        img[...] = 0
        pixels = np.array([[0,0]])
        area = 1
    else:
        max_index = stats[1:, cv2.CC_STAT_AREA].argmax() + 1
        img[labels != max_index] = 0
        img[labels == max_index] = 255
        pixels = np.transpose(np.where(labels == max_index))
        area = stats[max_index, cv2.CC_STAT_AREA]

    hull = cv2.convexHull(pixels).reshape(-1, 2)
    hull[:, [0, 1]]= hull[:, [1, 0]]

    return hull, area

def group_hull_vertex(hull, distance_threshold=0):
    '''
    Merge points in hull that are close to each other.
    '''
    vertex = list(hull)
    for i, u in enumerate(vertex):
        for j, v in enumerate(vertex):
            if i == j or u is None or v is None: continue
            if np.linalg.norm(u-v) < distance_threshold:
                vertex[i] = np.maximum(u, v)
                # vertex[i] = (u+v)//2
                vertex[j] = None
    hull = np.array([x for x in vertex if x is not None])

    return hull

def group_hull_edge(hull, angle_threshold=0.75):
    vertex = [hull[0], hull[1]]

    for i, u in enumerate(hull[2:]):
        # cross = np.cross(u-v, v-w) / np.linalg.norm(u-v) / np.linalg.norm(v-w)
        v, w = vertex[-1] - vertex[-2], u - vertex[-1]
        cos = np.dot(v, w) / np.linalg.norm(v) / np.linalg.norm(w)
        if cos > angle_threshold:
            vertex[-1] = u
        else:
            vertex.append(u)

    return np.array(vertex)

def get_candidate_edges(hull, width, height, EDGE_PROXIMITY=10):
    edges = []
    for i, (u, v) in enumerate(zip(hull, np.vstack((hull[1:], hull[:1])))):
            # Ignore hull edges that are near image edges
            if u[0] < EDGE_PROXIMITY and v[0] < EDGE_PROXIMITY: continue
            if u[1] < EDGE_PROXIMITY and v[1] < EDGE_PROXIMITY: continue
            if u[0] > width - EDGE_PROXIMITY and v[0] > width - EDGE_PROXIMITY: continue
            if u[1] > height - EDGE_PROXIMITY and v[1] > height - EDGE_PROXIMITY: continue
            edges.append((u, v))

    return np.array(edges)

def line_intersection(A, B):

    det = (A[1][0] - A[0][0]) * (B[0][1] - B[1][1]) - (A[1][1] - A[0][1]) * (B[0][0] - B[1][0])
    if det == 0: return [-1, -1]

    s = ((A[1][0] - A[0][0]) * (B[0][1] - A[0][1]) - (A[1][1] - A[0][1]) * (B[0][0] - A[0][0])) / det

    return (1-s)*B[0] + s*B[1]

def line_segment_intersection(P, v, A, B):
    '''
    Check whether a straight line intersects with a line segment.
    Parameters:
        - P: A point that lies on the straight line.
        - v: The directional vector of the straight line.
        - A, B: Two endpoints of the line segment. Represented by two 2D tuples.
    Returns: True or False, whether intersects or not.
    '''
    # P[0] + v[0]*t = (1-s) * A[0] + s * B[0]
    # P[1] + v[1]*t = (1-s) * A[1] + s * B[1]
    # <=>
    # v[0] * t + (A[0] - B[0]) * s = A[0] - P[0]
    # v[1] * t + (A[1] - B[1]) * s = A[1] - P[1]
 
    det = v[0] * (A[1] - B[1]) - v[1] * (A[0] - B[0])
    if det == 0: return False
 
    s = (v[0] * (A[1] - P[1]) - v[1] * (A[0] - P[0])) / det
    return (0 <= s <= 1)

def find_corners(edges, width, height, angle_threshold_parallel=0.9, angle_threshold_perpendicular=0.95):
    # Find longest edge
    max_edge = -1
    max_dist = 0
    for i, edge in enumerate(edges):
        dist = np.linalg.norm(edge[1] - edge[0])
        if dist > max_dist:
            max_dist = dist
            max_edge = i
    
    if max_edge == -1:
        return np.array([[0, 0], [width, 0], [width, height], [0, height]]), \
                -1,-1,-1,-1
    _max_edge = edges[max_edge][1] - edges[max_edge][0]
 
    # Find longest edge's parallel
    max_edge_parallel = -1
    max_dist_parallel = 0
    for i, edge in enumerate(edges):
        if i == max_edge: continue
        dist = np.linalg.norm(edge[1] - edge[0])
        # Check if parallel
        cos = np.dot(_max_edge, edge[1] - edge[0]) / dist / max_dist
        if abs(cos) < angle_threshold_parallel: continue
 
        if dist > max_dist_parallel:
            max_dist_parallel = dist
            max_edge_parallel = i
 
    # Find longest edge's perpendicular1
    max_edge_p1 = -1
    max_dist_p1 = 0
    for i, edge in enumerate(edges):
        if i == max_edge: continue
        if i == max_edge_parallel: continue
        dist = np.linalg.norm(edge[1] - edge[0])
        # Check if not parallel
        cos = np.dot(_max_edge, edge[1] - edge[0]) / dist / max_dist
        if abs(cos) > angle_threshold_perpendicular: continue
 
        if dist > max_dist_p1:
            max_dist_p1 = dist
            max_edge_p1 = i
 
    # Find longest edge's perpendicular2
    max_edge_p2 = -1
    max_dist_p2 = 0
    for i, edge in enumerate(edges):
        if i == max_edge: continue
        if i == max_edge_parallel: continue
        if i == max_edge_p1: continue
        dist = np.linalg.norm(edge[1] - edge[0])
        # Check if not parallel
        cos = np.dot(_max_edge, edge[1] - edge[0]) / dist / max_dist
        if abs(cos) > angle_threshold_perpendicular: continue
 
        if dist > max_dist_p2:
            max_dist_p2 = dist
            max_edge_p2 = i
 
    if max_edge == -1 or max_edge_parallel == -1 or max_edge_p1 == -1 or max_edge_p2 == -1:
        return np.array([[0, 0], [width, 0], [width, height], [0, height]]), \
                max_edge, max_edge_parallel, max_edge_p1, max_edge_p2
 
    return np.array([line_intersection(edges[max_edge], edges[max_edge_p1]),
                     line_intersection(edges[max_edge_p1], edges[max_edge_parallel]),
                     line_intersection(edges[max_edge_parallel], edges[max_edge_p2]),
                     line_intersection(edges[max_edge_p2], edges[max_edge]),], dtype=np.int32), \
            max_edge, max_edge_parallel, max_edge_p1, max_edge_p2

def order_points(pts):
    def centeroidpython(data):
        x, y = zip(*data)
        l = len(x)
        return sum(x) / l, sum(y) / l
 
    centroid_x, centroid_y = centeroidpython(pts)
    xy_sorted = sorted(pts, key = lambda x: np.arctan2((x[1]-centroid_y),(x[0]-centroid_x)))
    return np.array(xy_sorted)

def get_color_mask(img_hsv, lower_bound, upper_bound):
    hist = img_hsv[np.where(cv2.inRange(img_hsv[..., 0], lower_bound, upper_bound))]
    X = np.random.choice(hist[..., 1], 1000)

    # Calculate Gaussian Mixture Model
    gm = GaussianMixture(n_components=2, covariance_type='spherical', random_state=42).fit(X.reshape(-1, 1))

    # # Plot the PDF.
    # plt.hist(X, bins=50)
    # xmin, xmax = plt.xlim()
    # ymin, ymax = plt.ylim()
    # x = np.linspace(xmin, xmax, 100)

    # p = norm.pdf(x, gm.means_[0, 0], np.sqrt(gm.covariances_[0])) * ymax
    # plt.plot(x, p, 'k', linewidth=2)
    # p = norm.pdf(x, gm.means_[1, 0], np.sqrt(gm.covariances_[1])) * ymax
    # plt.plot(x, p, 'k', linewidth=2)

    # plt.show()

    max_index = gm.means_.reshape(-1).argmax()
    gm_lower = gm.means_[max_index, 0] - 3*np.sqrt(gm.covariances_[max_index])
    gm_upper = gm.means_[max_index, 0] + 3*np.sqrt(gm.covariances_[max_index])

    ## GET COLOR MASK

    # Create color segmentation mask
    lower = (lower_bound, gm_lower, 60)
    upper = (upper_bound, gm_upper, 255)
    img_masked = cv2.inRange(img_hsv, lower, upper)

    hull, area = get_convex_hull(img_masked)

    return hull, area, img_masked


def detect_billiards_table(img):
    height, width = img.shape[:2]
    t = time()
 
    # Blur image
    img_blur = cv2.GaussianBlur(img, (11, 11), 0)
 
 
    # Convert to HSV color space and equalize histogram
    img_hsv = cv2.cvtColor(img_blur, cv2.COLOR_BGR2HSV)
    # img_hsv[1] = cv2.equalizeHist(img_hsv[1])
    # img_hsv[2] = cv2.equalizeHist(img_hsv[2])
 
    hull_blue, area_blue, img_masked = get_color_mask(img_hsv, 80, 130)
    hull_green, area_green, img_masked = get_color_mask(img_hsv, 40, 70)
 
    # Determine larger hull
    if area_blue > area_green:
        hull = hull_blue
        area = area_blue
    else:
        hull = hull_green
        area = area_green
 
    distance_threshold = np.sqrt(area) * 0.02
    hull = group_hull_vertex(hull, distance_threshold)
 
    angle_threshold=0.99
    hull = group_hull_edge(hull, angle_threshold)
 
    # # Show convex hull
    # img_hull = np.zeros_like(img)
    # img_hull = cv2.fillPoly(img_hull, [hull], color=(255, 255, 255))
    # for pts in hull:
    #     img_hull = cv2.circle(img_hull, tuple(pts), 3, color=(0,0,255), thickness=-1)
    # cv2_imshow(img_hull)
 
    EDGE_PROXIMITY = width * 0.02
 
    edges = get_candidate_edges(hull, width, height, EDGE_PROXIMITY)
 
    # img_hull = cv2.polylines(img.copy(), edges, isClosed=False, color=(0,0,255), thickness=2)
    # cv2_imshow(img_hull)
 
    angle_threshold_parallel = 0.85
    angle_threshold_perpendicular = 0.95
 
    pts, max_edge, max_edge_parallel, max_edge_p1, max_edge_p2 = find_corners(
        edges, width, height, angle_threshold_parallel, angle_threshold_perpendicular)
 
    img_hull = img.copy()
    img_hull = cv2.polylines(img_hull, [edges[max_edge]], isClosed=False, color=(0,0,255), thickness=3)
    img_hull = cv2.polylines(img_hull, [edges[max_edge_parallel]], isClosed=False, color=(0,255,0), thickness=3)
    img_hull = cv2.polylines(img_hull, [edges[max_edge_p1]], isClosed=False, color=(0,255,255), thickness=3)
    img_hull = cv2.polylines(img_hull, [edges[max_edge_p2]], isClosed=False, color=(255,0,255), thickness=3)
    # cv2_imshow(img_hull)
 
    # print(time() - t)
 
    BORDER_WIDTH = 100
    border_pts = pts + [BORDER_WIDTH, BORDER_WIDTH]
    img = cv2.copyMakeBorder(img, BORDER_WIDTH, BORDER_WIDTH, BORDER_WIDTH, BORDER_WIDTH, cv2.BORDER_CONSTANT)
    img = cv2.polylines(img, [border_pts], isClosed=True, color=(0,0,255), thickness=2)
 
    return img, img_hull, order_points(pts) / [width, height]


def line_intersection(A, B):

    det = (A[1][0] - A[0][0]) * (B[0][1] - B[1][1]) - (A[1][1] - A[0][1]) * (B[0][0] - B[1][0])
    if det == 0: return None

    s = ((A[1][0] - A[0][0]) * (B[0][1] - A[0][1]) - (A[1][1] - A[0][1]) * (B[0][0] - A[0][0])) / det

    return (1-s)*B[0] + s*B[1]


def order_points(pts):
    def centeroidpython(data):
        x, y = zip(*data)
        l = len(x)
        return sum(x) / l, sum(y) / l
 
    centroid_x, centroid_y = centeroidpython(pts)
    xy_sorted = sorted(pts, key = lambda x: np.arctan2((x[1]-centroid_y),(x[0]-centroid_x)))
    return np.array(xy_sorted)


