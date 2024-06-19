#!/bin/bash

mkdir build 2> /dev/null
cd build

cmake -S .. -G "Unix Makefiles"
cmake --build .
