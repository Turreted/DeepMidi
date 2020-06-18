# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# define c++ version
set(CMAKE_CXX_STANDARD 11)

# project name
project( DeepMidi )


# flags

# files
set(SRCS
    ./src/MidiEncoder.cpp
    ./src/MidiDecoder.cpp
    ./src/decoder.cpp
    ./src/encoder.cpp
)

set(HDRS
    ./include/MidiEncoder.h
    ./include/MidiDecoder.h
)

# set binary output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# include
include_directories( ./include ./src ./libs/midifile/include ./libs/cnpy )

# add helper classes as static libraries
add_library(MidiDecoder STATIC ./src/MidiDecoder.cpp)
add_library(MidiEncoder STATIC ./src/MidiEncoder.cpp)

# add main executables
add_executable( midiDecoder ./src/decoder.cpp)
add_executable( midiEncoder ./src/encoder.cpp)

# link Public Libraries
add_subdirectory( ./libs/midifile )
target_link_libraries( MidiDecoder PUBLIC midifile )
target_link_libraries( MidiEncoder PUBLIC midifile )

add_subdirectory( ./libs/cnpy )
target_link_libraries( MidiDecoder PUBLIC cnpy )
target_link_libraries( MidiEncoder PUBLIC cnpy )

# link static Libraries
target_link_libraries( midiDecoder MidiDecoder )
target_link_libraries( midiEncoder MidiEncoder )
