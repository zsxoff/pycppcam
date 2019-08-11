# distutils: language = c++

from py_camera cimport CppCamera, Errors

cdef class CameraException(Exception):
    pass


cdef class FormatError(CameraException):
    pass


cdef class BufReqError(CameraException):
    pass


cdef class BufQueryError(CameraException):
    pass


cdef class MmapError(CameraException):
    pass


cdef class StreamOnError(CameraException):
    pass


cdef class BufQbufError(CameraException):
    pass


cdef class BufDqbufError(CameraException):
    pass


cdef class StreamOffError(CameraException):
    pass


cdef class MunmapError(CameraException):
    pass


cdef class Camera:
    cdef CppCamera *cam

    def __cinit__(self):
        self.cam = new CppCamera()

    def __dealloc__(self):
         del self.cam

    def init(self, device, size):
        cdef int w = size[0]
        cdef int h = size[1]

        cdef int err = self.cam.init(str.encode(device), w, h)

        if err == 0:
            return 0
        elif err == Errors.ERROR_OPEN:
            raise IOError()
        elif err == Errors.ERROR_FORMAT:
            raise FormatError()
        elif err == Errors.ERROR_REQBUFS:
            raise BufReqError()
        elif err == Errors.ERROR_QUERYBUF:
            raise BufQueryError()
        elif err == Errors.ERROR_MMAP:
            raise MmapError()
        else:
            raise Exception()

    def start_capture(self):
        cdef int err = self.cam.start_capture()

        if err == 0:
            return 0
        elif err == Errors.ERROR_STREAMON:
            raise StreamOnError()
        else:
            raise Exception()

    def read_frame(self):
        cdef int err = self.cam.read_frame()

        if err == 0:
            return 0
        elif err == Errors.ERROR_QBUF:
            raise BufQbufError()
        elif err == Errors.ERROR_DQBUF:
            raise BufDqbufError()
        else:
            raise Exception()

    def stop_capture(self):
        cdef int err = self.cam.stop_capture()

        if err == 0:
            return 0
        elif err == Errors.ERROR_STREAMOFF:
            raise StreamOffError()
        else:
            raise Exception()

    def release(self):
        cdef int err = self.cam.release()

        if err == 0:
            return 0
        elif err == Errors.ERROR_MUNMAP:
            raise MunmapError()
        elif err == Errors.ERROR_CLOSE:
            raise IOError()
        else:
            raise Exception()

    def get_frame(self):
        return self.cam.get_frame()

    def get_frame_bytesused(self):
        return self.cam.get_frame_bytesused()

    def get_frame_timestamp(self):
        return self.cam.get_frame_timestamp()
