#ifndef CPP_CAMERA_H
#define CPP_CAMERA_H

#include <fcntl.h>
#include <limits.h>
#include <linux/videodev2.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#define MAX_IMG_SIZE 10 * 1024 * 1024 // max img size in bytes

enum ERRORS {
  ERROR_OPEN = INT_MIN,
  ERROR_FORMAT,
  ERROR_REQBUFS,
  ERROR_QUERYBUF,
  ERROR_MMAP,
  ERROR_STREAMON,
  ERROR_QBUF,
  ERROR_DQBUF,
  ERROR_STREAMOFF,
  ERROR_MUNMAP,
  ERROR_CLOSE
};

class CppCamera {
private:
  int m_fd = -1;                      // file descriptor.
  void *m_buffer_start = nullptr;     // pointer to start of frame buffer.
  unsigned int m_querybuf_length = 0; // querybuf size in bytes.

  struct v4l2_buffer m_v4l2_qbuf = {
      0,                           // index
      V4L2_BUF_TYPE_VIDEO_CAPTURE, // type
      0,                           // bytesused
      0,                           // flags
      0,                           // fiels
      {},                          // timestamp
      {},                          // timecode
      0,                           // sequence
      V4L2_MEMORY_MMAP,            // memory
      {},                          // m
      0,                           // length
      0,                           // reserved2
      {},                          // {request_fd, reserved}
  };

  struct v4l2_buffer m_v4l2_dqbuf = {
      0,                           // index
      V4L2_BUF_TYPE_VIDEO_CAPTURE, // type
      0,                           // bytesused
      0,                           // flags
      0,                           // fiels
      {},                          // timestamp
      {},                          // timecode
      0,                           // sequence
      V4L2_MEMORY_MMAP,            // memory
      {},                          // m
      0,                           // length
      0,                           // reserved2
      {},                          // {request_fd, reserved}
  };

  int rioctl(unsigned long req, const void *arg);

public:
  CppCamera();

  virtual ~CppCamera();

  int init(const std::string &device, int width, int height);

  int start_capture();

  int read_frame();

  std::string get_frame();

  int stop_capture();

  int release();

  unsigned int get_frame_bytesused();

  timeval get_frame_timestamp();
};

#endif // CPP_CAMERA_H