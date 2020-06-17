#include "MidiDecoder.h"
#include "MidiEncoder.h"

int main(){
    MidiDecoder bob;
    MidiEncoder alice;
    
    bob.load("./data/classical.midi");
    bob.save("test.npy");

    alice.load("test.npy");
    alice.save("classical.midi");

    return 0;
}
