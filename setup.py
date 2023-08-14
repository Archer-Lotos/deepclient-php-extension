from setuptools import setup, find_packages
from distutils.core import setup
from Cython.Build import cythonize

setup(
    name="deepclient",
    version="1.0.1", 
    packages=find_packages(),
    install_requires=[
        # Add your package dependencies here
    ],
    description="Deep Client - a way to connect your favorite language with Deep",
    long_description="Deep Client - a way to connect your favorite language with Deep",
    license="Unlicense",
    url="https://github.com/lotos2021/deepclient-php-extension",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "License :: OSI Approved :: The Unlicense (Unlicense)",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
    ],
    ext_modules=cythonize("deepclient.pyx")
)
