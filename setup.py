#!/usr/bin/env python

from setuptools import setup, Extension
from Cython.Build import cythonize


def main():
    compiler_directives = {
        'language_level': '3',
        'embedsignature': True,
        'c_string_encoding': 'utf-8'
    }

    ext_modules = cythonize(
        [
            Extension(
                'cppcam',
                [
                    'src/cppcam.pyx',
                ],
                extra_compile_args=[
                    "-std=c++11",
                ],
                extra_link_args=[
                    "-std=c++11",
                ],
            )
        ],
        compiler_directives=compiler_directives,
    )

    setup(name='cppcam',
          version='0.1.0',
          description='Simple Cython binding for C++ V4L Camera',
          author='Konstantin Dobratulin',
          author_email='zsxoff@gmail.com',
          ext_modules=ext_modules)


if __name__ == "__main__":
    main()
