# cppcam

[![Build Status](https://travis-ci.org/zsxoff/cppcam.svg?branch=master)](https://travis-ci.org/zsxoff/cppcam)

**cppcam** is a simple library for get image with a webcam for Python. The program uses code written in C++ with [Cython](https://cython.org/) bindings.

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
* pip
* cython
* gcc
* g++

### Ubuntu

```bash
sudo apt-get install python3 python3-pip gcc g++
pip3 install --user cython
```

### Debian

see *Ubuntu*.

### Fedora

```bash
sudo dnf install python3 python3-pip python3-devel gcc gcc-c++
pip3 install --user cython
```

### Arch Linux

```bash
sudo pacman -S --needed python python-pip gcc
pip3 install --user cython
```

## **Installation**

Clone this repo and go to project folder:

```bash
git clone https://github.com/zsxoff/cppcam.git
cd cppcam
```

Run command in project directory

```bash
pip3 install --user .
```

or

```bash
python3 -m pip install --user .
```

If you use `venv`, `virtualenv` or `anaconda`, you don't need `--user` option.

Finally, see examples in `examples` directory or run tests in `tests` if you want it.

## **Known issues**

**Issue**: `gcc` throws exceptions at compile process like `only available with -std=c++11`.
**Solution**: execute command `export CFLAGS="-std=c++11"` before install command.

**Issue**: `gcc` throws exceptions at compile process `fatal error: Python.h: No such file or directory`.
**Solution**: check if you installed `python3-devel` package.

**Issue**: Camera raise `cppcam.BufDqbufError` during `read_frame()`.
**Solution**: Try to change `#define MAX_IMG_SIZE` in `src/cpp_camera.h` like `20 * 1024 * 1024` or bigger, where `20` is a maximum size of image in megabytes.
