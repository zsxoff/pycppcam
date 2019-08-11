#!/usr/bin/env python3

import numpy as np
import cv2

from cppcam import Camera

cam = Camera()
cam.init('/dev/video0', (1280, 720))
cam.start_capture()

while True:
    # Read new frame to camera buffer
    cam.read_frame()

    # Get buffer image-bytes content
    raw = cam.get_frame()

    # Convert image raw data to uint array
    arr = np.frombuffer(raw, np.uint8)

    # Read image from array
    img = cv2.imdecode(arr, cv2.IMREAD_COLOR)

    cv2.imshow('frame', img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam.stop_capture()
cam.release()
