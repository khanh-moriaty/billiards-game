import detect_function
import segment_function

from flask import Flask, request
import requests
import os
import base64

app = Flask(__name__)

@app.route("/<img_path>")
def listen(img_path):
    img_path = base64.b64decode(img_path).decode()
    print(img_path)
    # Load image & corner's coordinate
    img = detect_function.load_image(img_path)

    # Image size after tranform
    new_w, new_h = 1000, 500

    _, _, pts = segment_function.detect_billiards_table(img)

    img_trans, img_detected, new_coord = detect_function.detect_ball(img, pts, 1000, 500)
    if(len(new_coord) == 0):
        res = ''
    else:
        res = '\n'.join([str(x[0]) + " " + str(x[1]) for x in new_coord])
    
    print(res)

    return res
    
if __name__ == '__main__':
   app.run('localhost', port=5678, debug=True)



