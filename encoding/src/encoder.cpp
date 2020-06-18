#include <iostream>
#include <string>
#include <sys/stat.h>
#include <bits/stdc++.h> 

#include "MidiEncoder.h"


bool fileExists(const char* fileBuf){
    // test if file exists 
    std::ifstream infile(fileBuf);
    return infile.good();
}

int main(int argc, char** argv){
    MidiEncoder midiencoder;
    
    //std::string inFile = std::string(argc[1]);

    if (argc < 3){
        std::cout << "format: ./midiEncoder inputFile.midi outputFile.npy" << std::endl;
        return 1;
    }

    if (!fileExists(argv[1])){
        std::cout << "File " << std::string(argv[1]) << " Does not exist" << std::endl;
        return 1;
    }
    
    midiencoder.load(argv[1]);
    midiencoder.save(argv[2]);

    return 0;
}
