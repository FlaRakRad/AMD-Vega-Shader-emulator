#!/bin/bash
set -e
cd libs
g++ -std=c++20 -O3 -c vega.cpp -o vega.o 
ar rcs libvega.a vega.o
cd ..
