# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# define c++ version
set_property(TARGET tgt PROPERTY CXX_STANDARD 11)

# project name
project( DeepMidi )


# flags

# files
set(SRCS
    src/MidiEncoder.cpp
    src/MidiDecoder.cpp
    src/main.cpp
)

set(HDRS
    include/MidiEncoder.cpp
    include/MidiDecoder.cpp
)

# include
include_directories( ./include ./src ./libs/midifile/include ./libs/cnpy )

# add helper classes as static libraries
add_library(MidiDecoder STATIC ./src/MidiDecoder.cpp)
add_library(MidiEncoder STATIC ./src/MidiEncoder.cpp)

# add main executable
add_executable( main ./src/main)

# link Public Libraries
add_subdirectory( ./libs/midifile )
target_link_libraries( MidiDecoder PUBLIC midifile )

add_subdirectory( ./libs/cnpy )
target_link_libraries( MidiDecoder PUBLIC cnpy )

# link static Libraries
target_link_libraries( main MidiDecoder )
target_link_libraries( main MidiEncoder )
