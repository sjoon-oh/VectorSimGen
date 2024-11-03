#!/bin/bash

rm CMakeCache.txt
rm cmake_install.cmake

rm Makefile
rm -rf uild

cmake .
make -j