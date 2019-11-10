#!/usr/bin/env python

import unittest

import cppcam


class TestError(unittest.TestCase):
    def test_init_error(self):
        cam = cppcam.Camera()
        with self.assertRaises(IOError):
            cam.init('/dev/wtf', (1280, 720))

    def test_start_capture_error(self):
        cam = cppcam.Camera()
        with self.assertRaises(cppcam.StreamOnError):
            cam.start_capture()

    def test_read_frame_error(self):
        cam = cppcam.Camera()
        with self.assertRaises(cppcam.BufQbufError):
            cam.read_frame()

    def test_stop_capture_error(self):
        cam = cppcam.Camera()
        with self.assertRaises(cppcam.StreamOffError):
            cam.stop_capture()

    def test_release_error(self):
        cam = cppcam.Camera()
        with self.assertRaises(cppcam.MunmapError):
            cam.release()

    def test_get_empty_frame(self):
        cam = cppcam.Camera()
        self.assertEqual(cam.get_frame(), b'')

    def test_get_empty_frame_bytesused(self):
        cam = cppcam.Camera()
        self.assertEqual(cam.get_frame_bytesused(), 0)

    def test_get_empty_frame_timestamp(self):
        cam = cppcam.Camera()
        timestamp = cam.get_frame_timestamp()

        self.assertEqual(timestamp['tv_sec'], 0)
        self.assertEqual(timestamp['tv_usec'], 0)


if __name__ == '__main__':
    unittest.main()
