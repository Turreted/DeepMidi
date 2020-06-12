#!/bin/sh

# compile cpp binaries
mkdir ./encoding/build
cd ./encoding/build
cmake ..
cd .. && make

