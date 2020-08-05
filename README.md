# pycppcam

> Simple webcam library for Python 3 written in C++ with Cython.

---

[![Build Status](https://travis-ci.org/zsxoff/pycppcam.svg?branch=master)](https://travis-ci.org/zsxoff/pycppcam)

---

**pycppcam** is a simple library for get image with a webcam for Python. The program uses code written in C++ with [Cython](https://cython.org/) bindings.

*Disclaimer:* This project was created more as an experimental one and is unlikely to develop towards supporting new features. Use it if you really need it.

## Example

```python
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
```

See more in `examples` dir.

## Dependencies

* python3
* gcc
* g++

On Ubuntu you can install it like:

```bash
sudo apt-get install python3 python3-pip gcc g++
```

## **Installation**

Clone this repo and go to project folder:

```bash
git clone https://github.com/zsxoff/pycppcam.git
cd pycppcam
pip install --user -r requirements.txt
pip install --user .
```

If you use [venv](<https://docs.python.org/3/library/venv.html>), [Virtualenv](<https://virtualenv.pypa.io/en/latest/>), [Anaconda](<https://www.anaconda.com/>) and etc., you don't need `--user` option.

## **Known issues**

**Issue**: `gcc` throws exceptions at compile process like `only available with -std=c++11`.
**Solution**: execute command `export CFLAGS="-std=c++11"` before install command.

**Issue**: `gcc` throws exceptions at compile process `fatal error: Python.h: No such file or directory`.
**Solution**: check if you installed `python3-devel` package.

**Issue**: Camera raise `cppcam.BufDqbufError` during `read_frame()`.
**Solution**: Try to change `#define MAX_IMG_SIZE` in `src/cpp_camera.h` like `20 * 1024 * 1024` or bigger, where `20` is a maximum size of image in megabytes.

## TODO

* Fix camera raise `cppcam.BufDqbufError` during `read_frame()` due to `#define MAX_IMG_SIZE` in `src/cpp_camera.h`.
* Improve `setup.py` file.

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)](https://opensource.org/licenses/MIT)

This project is licensed under the terms of the [MIT](https://opensource.org/licenses/MIT) license (see [LICENSE](<https://github.com/zsxoff/pycppcam/blob/master/LICENSE>) file).
