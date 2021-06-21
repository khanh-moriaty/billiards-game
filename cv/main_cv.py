import detect_function
import segment_function

# Load image & corner's coordinate
img = detect_function.load_image('mpz.00.jpg')

# Image size after tranform
new_w, new_h = 1000, 500

_, _, pts = segment_function.detect_billiards_table(img)

img_trans, img_detected, new_coord = detect_function.detect_ball(img, pts, 1000, 500)

for i in range(len(new_coord)):
    print(new_coord[i][0], new_coord[i][1])
