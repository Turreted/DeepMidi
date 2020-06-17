#!/bin/sh

# install external libs
git clone https://github.com/rogersce/cnpy.git ./encoding/libs/cnpy
git clone https://github.com/craigsapp/midifile.git ./encoding/libs/midifile

# Download dataset
cd dataset
wget https://storage.googleapis.com/magentadata/datasets/maestro/v2.0.0/maestro-v2.0.0-midi.zip
unzip maestro-v2.0.0-midi.zip
rm maestro-v2.0.0-midi.zip
cd ..

# compile cpp binaries
mkdir ./encoding/build
cd ./encoding/build

cmake ..
make
