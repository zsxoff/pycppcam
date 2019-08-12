#!/usr/bin/env python

from cppcam import Camera

# Init camera
cam = Camera()
cam.init('/dev/video0', (1280, 720))

# Read frame to in-memory buffer
cam.start_capture()
cam.read_frame()

# Get raw data
raw = cam.get_frame()

# Close camera
cam.stop_capture()
cam.release()
