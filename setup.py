#!/usr/bin/env python

"""Setup file for pycppcam."""

from Cython.Build import cythonize
from setuptools import Extension, setup


def main():
    """Setup script."""
    compiler_directives = {
        "language_level": "3",
        "embedsignature": True,
        "c_string_encoding": "utf-8",
    }

    ext_modules = cythonize(
        [
            Extension(
                "cppcam",
                ["src/cppcam.pyx",],
                extra_compile_args=["-std=c++11",],
                extra_link_args=["-std=c++11",],
            )
        ],
        compiler_directives=compiler_directives,
    )

    setup(
        name="cppcam",
        version="0.1.0",
        description="Simple Cython binding for C++ V4L Camera",
        author="Konstantin Dobratulin",
        ext_modules=ext_modules,
    )


if __name__ == "__main__":
    main()
