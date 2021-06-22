import cv2
import numpy as np
import matplotlib.pyplot as plt
from time import time
import os
from PIL import Image, ImageDraw
from matplotlib.path import Path
import pylab as plt
import math
import argparse
import glob
from math import sqrt, atan2, pi
from PIL import Image, ImageDraw
from math import sqrt, pi, cos, sin
from collections import defaultdict

# Load image and resize 1000x1000
def load_image(path): 

    img = cv2.imread(path, cv2.IMREAD_COLOR)
    h, w = img.shape[:2]
    if h > 1000:
        img = cv2.resize(img, (1000*w//h, 1000))

    return img


# Load 4 corners from file, return a list of 4 tuples
def load_pts(pts_path):

    pts = []

    fi_pts = open(pts_path, 'r+')

    pts1 = fi_pts.readline()
    pts2 = fi_pts.readline()
    pts3 = fi_pts.readline()
    pts4 = fi_pts.readline()

    coord = pts1.split()
    pts.append((float(coord[1]), float(coord[2])))
    coord = pts2.split()
    pts.append((float(coord[1]), float(coord[2])))
    coord = pts3.split()
    pts.append((float(coord[1]), float(coord[2])))
    coord = pts4.split()
    pts.append((float(coord[1]), float(coord[2])))

    fi_pts.close()

    return pts


# Use polygon mask to remove background around the table
def remove_bg(img, pts):

    h, w = img.shape[:2]

    # 4 corners's coord
    top_left = pts[0]
    top_right = pts[1]
    bot_right = pts[2]
    bot_left = pts[3]

    # Create polygon mask
    polygon = [(bot_left[0]*w, bot_left[1]*h), (top_left[0]*w, top_left[1]*h), (top_right[0]*w, top_right[1]*h), (bot_right[0]*w, bot_right[1]*h)]
    img2 = Image.new('L', (w, h), 0)
    ImageDraw.Draw(img2).polygon(polygon, outline=1, fill=255)
    mask = np.array(img2)

    # Remove background
    masked = cv2.bitwise_and(img, img, mask=mask)

    return masked


# Hough circle: Detect ball
def hough_circle(img, img_draw):

    # Apply hough transform on the image
    circles = cv2.HoughCircles(img, cv2.HOUGH_GRADIENT, 1, 20, param1=200, param2=13, minRadius=5, maxRadius=20)
    # circles = cv2.HoughCircles(img_blur, cv2.HOUGH_GRADIENT, 1, 20, param1=200, param2=10, minRadius=5, maxRadius=20)
    # circles = cv2.HoughCircles(img_blur, cv2.HOUGH_GRADIENT, 1, 50, param1=200, param2=10, minRadius=5, maxRadius=20)

    # Draw detected circles
    img_draw = img_draw.copy()
    if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                    # Draw outer circle
                    cv2.circle(img_draw, (i[0], i[1]), i[2], (0, 0, 255), 3)
                    # Draw inner circle
                    # cv2.circle(img_draw, (i[0], i[1]), 2, (0, 0, 255), 3)
                    
    else:
        print('No circle')

    return img_draw, circles


# Perspective transform image: from real angle to top-down angle

def perspective_trans(img, pts, new_w = 1000, new_h = 500):
    
    h, w = img.shape[:2]

    # 4 corners's coord
    top_left = pts[0]
    top_right = pts[1]
    bot_right = pts[2]
    bot_left = pts[3]

    # pts1: list of 4 corners's location in order: top_left, top_right, bot_left, bot_right
    # pts2: list of 4 coordinates in the result image
    pts1 = np.float32([[top_left[0]*w, top_left[1]*h], [top_right[0]*w, top_right[1]*h], [bot_left[0]*w, bot_left[1]*h], [bot_right[0]*w, bot_right[1]*h]])
    pts2 = np.float32([[0, 0], [new_w, 0], [0, new_h], [new_w, new_h]])

    # Implement transform
    matrix = cv2.getPerspectiveTransform(pts1, pts2)
    rst = cv2.warpPerspective(img, matrix, (new_w, new_h), cv2.INTER_LINEAR, borderValue=(255, 255, 255))

    return rst, matrix


# Identify which is the long edge
# return 0: top_left-top_right
# return 1: top_left-bot_left

def identify_edge(img, pts):

    h, w = img.shape[:2]

    # Perspective transform to 500x500
    img_trans, matrix = perspective_trans(img, pts, 500, 500)

    # Convert to GRAY, equalize histogram and blur image
    img_id = img_trans.copy()
    img_id = cv2.cvtColor(img_id, cv2.COLOR_BGR2GRAY)
    img_id = cv2.equalizeHist(img_id)
    blurred = cv2.GaussianBlur(img_id, (5, 5), 0)

    # Use threshold to focus on the holes
    (T, thresh) = cv2.threshold(blurred, 20, 255, cv2.THRESH_BINARY)

    # Create a mask having 4 white squares in the center of left, right, top, bottom
    mask = np.zeros(img_id.shape[:2], dtype = 'uint8') # mask: grayscale
    mask[225:275, :50] = 255 #left
    mask[0:50, 225:275] = 255 #top
    mask[225:275, 450:500] = 255 #right
    mask[450:500, 225:275] = 255 #bot

    # Apply mask with threshold image
    masked = cv2.bitwise_and(thresh, thresh, mask=mask)

    # Conditions:

    # T1, T2: 1 trong các ô (left, right)/(top/bot) hoàn toàn trắng
    T1 = ((masked[225:275, :50].astype(int).sum() == 637500) | (masked[225:275, 450:500].astype(int).sum() == 637500))
    T2 = ((masked[0:50, 225:275].astype(int).sum() == 637500) | (masked[450:500, 225:275].astype(int).sum() == 637500))

    # T3: left+right có nhiều màu đen hơn top+bot
    T3 = masked[225:275, :50].astype(int).sum() + masked[225:275, 450:500].astype(int).sum() < masked[0:50, 225:275].astype(int).sum() + masked[450:500, 225:275].astype(int).sum()

    # T4: (ô left/right có ít màu đen hơn) có nhiều màu đen hơn (ô top/bot có nhiều màu đen hơn)
    T4 = (max(masked[225:275, :50].astype(int).sum(), masked[225:275, 450:500].astype(int).sum()) < min(masked[0:50, 225:275].astype(int).sum(), masked[450:500, 225:275].astype(int).sum()))
    
    # T5: (ô left/right có nhiều màu đen hơn) có ít màu đen hơn (ô top/bot có ít màu đen hơn)
    T5 = (min(masked[225:275, :50].astype(int).sum(), masked[225:275, 450:500].astype(int).sum()) > max(masked[0:50, 225:275].astype(int).sum(), masked[450:500, 225:275].astype(int).sum()))
    
    # T6: top có nhiều màu đen hơn left, right
    T6 = masked[0:50, 225:275].astype(int).sum() < min(masked[225:275, :50].astype(int).sum(), masked[225:275, 450:500].astype(int).sum())

    # T7, T8: left, right có màu đen nhiều hơn một ngưỡng
    T7 = masked[225:275, :50].astype(int).sum() < 580000
    T8 = masked[225:275, 450:500].astype(int).sum() < 580000

    # T9: bot có ít màu đen hơn một ngưỡng 
    T9 = masked[450:500, 225:275].astype(int).sum() > 600000


    if(T1 & T2):
        if(T3):
            cv2.circle(img_trans, (10, 255), 15, (0, 255, 255), 3)
            cv2.circle(img_trans, (490, 255), 15, (0, 255, 255), 3)
            return img_trans, masked, 1

        else:
            cv2.circle(img_trans, (255, 10), 15, (0, 0, 255), 3)
            cv2.circle(img_trans, (255, 490), 15, (0, 0, 255), 3)
            return img_trans, masked, 0

    if(T1):
        cv2.circle(img_trans, (255, 10), 15, (0, 0, 255), 3)
        cv2.circle(img_trans, (255, 490), 15, (0, 0, 255), 3)
        return img_trans, masked, 0

    if(T2):
        cv2.circle(img_trans, (10, 255), 15, (0, 255, 255), 3)
        cv2.circle(img_trans, (490, 255), 15, (0, 255, 255), 3)
        return img_trans, masked, 1

    if(T4):
        cv2.circle(img_trans, (10, 255), 15, (0, 255, 255), 3)
        cv2.circle(img_trans, (490, 255), 15, (0, 255, 255), 3)
        return img_trans, masked, 1

    if(T5):
        cv2.circle(img_trans, (255, 10), 15, (0, 0, 255), 3)
        cv2.circle(img_trans, (255, 490), 15, (0, 0, 255), 3)
        return img_trans, masked, 0

    if((T6 & (T7 | T8) & T9) | (T6 & T7 & T8)):
        cv2.circle(img_trans, (10, 255), 15, (0, 255, 255), 3)
        cv2.circle(img_trans, (490, 255), 15, (0, 255, 255), 3)
        return img_trans, masked, 1

    if(T3):
        cv2.circle(img_trans, (10, 255), 15, (0, 255, 255), 3)
        cv2.circle(img_trans, (490, 255), 15, (0, 255, 255), 3)
        return img_trans, masked, 1

    else:
        cv2.circle(img_trans, (255, 10), 15, (0, 0, 255), 3)
        cv2.circle(img_trans, (255, 490), 15, (0, 0, 255), 3)
        return img_trans, masked, 0


# Calculate new coordinate of balls detected after transforming
# circles: [[x, y, r]]
def cal_new_coord(matrix, circles):
    
    new_coord = []

    # y: no. of balls detected
    _, y, _ = circles.shape[:3]

    # Transform points
    for i in range(y):
        px = (matrix[0][0]*circles[0, i, 0] + matrix[0][1]*circles[0, i, 1] + matrix[0][2]) / ((matrix[2][0]*circles[0, i, 0] + matrix[2][1]*circles[0, i, 1] + matrix[2][2]))
        py = (matrix[1][0]*circles[0, i, 0] + matrix[1][1]*circles[0, i, 1] + matrix[1][2]) / ((matrix[2][0]*circles[0, i, 0] + matrix[2][1]*circles[0, i, 1] + matrix[2][2]))
        new_coord.append((int(px), int(py)))
    
    return new_coord


def detect_ball(img, pts, new_w = 1000, new_h = 500):

    h, w = img.shape[:2]

    # Hole's radius
    radius = 15

    # Remove background
    masked = remove_bg(img, pts)

    # Detect ball
    img_gray = cv2.cvtColor(masked, cv2.COLOR_BGR2GRAY)
    img_detected, circles = hough_circle(img_gray, masked)
    

    # Identify long edge
    img_id, _, f = identify_edge(masked, pts)

    # Perspective transform
    # If holes located in the left/right side, rotate image 90_COUNTERCLOCKWISE
    if(f == 1):
        img_trans, matrix = perspective_trans(masked, pts, new_h, new_w)
        img_trans = cv2.rotate(img_trans, cv2.ROTATE_90_COUNTERCLOCKWISE)
    else:
        img_trans, matrix = perspective_trans(masked, pts, new_w, new_h)

    # If ball exists
    if(np.all(circles != None)):

        # Calculate new coordinate of balls
        # new_coord: list of tuples, each tuple has 2 elements: w, h
        new_coord = cal_new_coord(matrix, circles)
     
        # If hole located in the left-right side, rotate points 90 degrees counterclockwise
        if((f == 1) & (len(new_coord) != 0)):
            tmp = np.array(new_coord.copy())
            tmp2 = tmp.copy()
            tmp2[:, 0] = tmp[:, 1]
            tmp2[:, 1] = new_h - tmp[:, 0]
            new_coord = map(tuple, tmp2)
            new_coord = list(new_coord)

        # Remove ball near hole & edge
        i = 0
        while(i < len(new_coord)):
            if( (np.array(new_coord[i])[0] < radius*2) | (np.array(new_coord[i])[0] > new_w - radius*2) | 
                        (np.array(new_coord[i])[1] < radius*2) | (np.array(new_coord[i])[1] > new_h - radius*2) ):
                new_coord.pop(i)
                i = i - 1
            i = i + 1
            
        new_coord = [(coord[0]/new_w, coord[1]/new_h) for coord in new_coord]

        return img_trans, img_detected, new_coord

    else:
        return 0
