# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( deepmidi )

# flags

# files

# include
include_directories( ./include ./src ./libs/midifile/include ./libs/cnpy )

# target
add_executable( binary ./src/decoder.cpp )
# add_executable( binary ./src/main.cpp )

# external libs

# midifile library
add_subdirectory( ./libs/midifile )
target_link_libraries( binary midifile )

# cnpy library
add_subdirectory( ./libs/cnpy )
target_link_libraries( binary cnpy )

