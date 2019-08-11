#include "cpp_camera.h"

CppCamera::CppCamera() = default;

CppCamera::~CppCamera() = default;

int CppCamera::rioctl(const unsigned long req, const void *arg) {
  int err = -1;
  unsigned int k = 0;

  while (k++ < MAX_IMG_SIZE) {
    err = ioctl(m_fd, req, arg);

    if (err >= 0) {
      break;
    }
  }

  return err;
}

int CppCamera::init(const std::string &device, const int width,
                    const int height) {
  /* Open device. */

  m_fd = open(device.c_str(), O_RDWR | O_NONBLOCK, 0);

  if (m_fd < 0) {
    return ERROR_OPEN;
  }

  /* Init format. */

  if (width <= 0 || height <= 0) {
    return ERROR_FORMAT;
  }

  const unsigned int u_width = static_cast<unsigned int>(width);
  const unsigned int u_height = static_cast<unsigned int>(height);

  struct v4l2_format image_format = {
      V4L2_BUF_TYPE_VIDEO_CAPTURE, // type
      {
          {
              u_width,                 // width
              u_height,                // height
              V4L2_PIX_FMT_MJPEG,      // pixelformat
              V4L2_FIELD_INTERLACED,   // field
              u_width,                 // bytesperline
              u_width * u_height,      // sizeimage
              V4L2_COLORSPACE_DEFAULT, // colorspace
          }                            // pix
      }                                // fmt
  };

  if (ioctl(m_fd, VIDIOC_S_FMT, &image_format) < 0) {
    return ERROR_FORMAT;
  }

  /* Init REQBUFS. */

  struct v4l2_requestbuffers v4l2_reqbufs = {
      1,                           // count
      V4L2_BUF_TYPE_VIDEO_CAPTURE, // type
      V4L2_MEMORY_MMAP,            // memory
  };

  if (ioctl(m_fd, VIDIOC_REQBUFS, &v4l2_reqbufs) < 0) {
    return ERROR_REQBUFS;
  }

  /* Init QUERYBUF. */

  struct v4l2_buffer v4l2_querybuf = {
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
      {},                          // union {request_fd, reserved}
  };

  if (ioctl(m_fd, VIDIOC_QUERYBUF, &v4l2_querybuf) < 0) {
    return ERROR_QUERYBUF;
  }

  /* Init MMAP. */

  m_buffer_start = mmap(nullptr,                // addr
                        v4l2_querybuf.length,   // len
                        PROT_READ | PROT_WRITE, // prot
                        MAP_SHARED,             // flags
                        m_fd,                   // fd
                        v4l2_querybuf.m.offset  // offset
  );

  if (m_buffer_start == MAP_FAILED) {
    return ERROR_MMAP;
  }

  m_querybuf_length = v4l2_querybuf.length;

  return 0;
}

int CppCamera::start_capture() {
  /* Init STREAMON. */

  enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (ioctl(m_fd, VIDIOC_STREAMON, &type) < 0) {
    return ERROR_STREAMON;
  }

  return 0;
}

int CppCamera::read_frame() {
  /* Load QBUF. */

  if (ioctl(m_fd, VIDIOC_QBUF, &m_v4l2_qbuf) < 0) {
    return ERROR_QBUF;
  }

  /* Load DQBUF. */

  if (rioctl(VIDIOC_DQBUF, &m_v4l2_dqbuf) < 0) {
    return ERROR_DQBUF;
  }

  return 0;
}

std::string CppCamera::get_frame() {
  if (m_fd < 0 || m_v4l2_dqbuf.bytesused == 0) {
    return "";
  }

  return std::string(static_cast<char *>(m_buffer_start),
                     m_v4l2_dqbuf.bytesused);
}

int CppCamera::stop_capture() {
  /* Init STREAMOFF. */

  enum v4l2_buf_type enum_streamoff = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (ioctl(m_fd, VIDIOC_STREAMOFF, &enum_streamoff) < 0) {
    return ERROR_STREAMOFF;
  }

  return 0;
}

int CppCamera::release() {
  /* Free MMAP. */

  if (munmap(m_buffer_start, m_querybuf_length) < 0) {
    return ERROR_MUNMAP;
  }

  /* Close device. */

  if (close(m_fd) < 0) {
    return ERROR_CLOSE;
  }

  return 0;
}

unsigned int CppCamera::get_frame_bytesused() { return m_v4l2_dqbuf.bytesused; }

timeval CppCamera::get_frame_timestamp() { return m_v4l2_dqbuf.timestamp; }