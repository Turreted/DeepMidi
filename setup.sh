#!/bin/sh

# install external libs
git clone https://github.com/rogersce/cnpy.git ./encoding/libs/cnpy
git clone https://github.com/craigsapp/midifile.git ./encoding/libs/midifile

# compile cpp binaries
mkdir ./encoding/build
cd ./encoding/build

cmake ..
make
