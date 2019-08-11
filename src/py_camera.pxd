from libcpp.string cimport string
from libc.limits cimport INT_MIN


cdef extern from "<bits/types.h>" nogil:
    ctypedef struct timeval:
        long tv_sec
        long tv_usec

cdef enum Errors:
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

cdef extern from "cpp_camera.cpp":
    pass

cdef extern from "cpp_camera.h":
    cdef cppclass CppCamera:
        CppCamera() except +
        
        int init(const string &device, int width, int height)

        int start_capture()

        int read_frame()

        string get_frame()

        int stop_capture()

        int release()

        unsigned int get_frame_bytesused()

        timeval get_frame_timestamp()
