#!/bin/bash

# Make build directory
mkdir -p build

# Enter build directory
cd build

# Compile and link the project
cmake ..
make
