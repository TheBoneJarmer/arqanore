#!/bin/bash

mkdir build 2> /dev/null
cd build

cmake -DBUILD_SHARED_LIBS=ON -S .. -G "MinGW Makefiles"

if [[ -z $1 ]]
then
    cmake --build . -t arqanore
else
    cmake --build . -t $1
fi
