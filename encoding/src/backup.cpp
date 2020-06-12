#include "MidiFile.h"
#include"cnpy.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace smf;

// We want there to be 4 ticks per quarter note
const static int TQP = 8;

// TODO: Seralize by converting to numpy array
// TODO: Convert array back to midi

/*
int roundRange(int inp, int min, double max){
    
    determine if a number is closer to the given min or max
    

   if ((double) inp >= min + ((max - min) / 2)){
       return (int) max;
   } else {
       return (int) min;
   }
}
*/


int main(int argc, char** argv) {
    string midiData = "./data/classical.midi";
    //string midiData = "./data/dylan.mid";

    MidiFile midifile(midiData);
    midifile.joinTracks();
   
    MidiEvent* mev;
    MidiEventList track = midifile[0];

    // Convert the midi data to absolute ticks. This means that time is measured
    // relative to the beginning of the file, not the previous event
    if (midifile.isAbsoluteTicks() < 1) {
        midifile.absoluteTicks();
    }

    // find the total tick length by finding the ticks of the final event
    mev = &track[track.size() - 2];
    int oldTickLength = mev->tick;

    int totalQuarterNotes = oldTickLength / midifile.getTicksPerQuarterNote();

    // we want there to only be a single tick per 16th note
    // TODO: that this needs to be specified in the new midi header
    int totalTicks = totalQuarterNotes * 8;
    double conversionRate = (oldTickLength / totalTicks);

    // Reduce the file into an array
    int midiInputRange = 127;
    int MidiFileArray[totalTicks + 100][midiInputRange];

    // currentick tracks where we are in the MidiFileArray
    // it is moved up once a midiEvent tick value is greater
    // than the currentTick value
    int currentTick = 0;

    for (int event = 0; event < track.size(); event++) {

        mev = &track[event];
        int tickValue = mev->tick / conversionRate;

        if (currentTick <= tickValue && tickValue < currentTick + 1){

            // determine if the given midi event is closer in time to the
            // currentTick or the next tick
            // int tickPosition = roundRange(tickValue, currentTick, currentTick + 1)

            // Check if midi event is to spawn a note, remove a note, or header data
            int binaryCommand = (int)(*mev)[0];

            // Define pitch and velocity values
            int pitchValue    = (int)(*mev)[1];
            int velocityValue = (int)(*mev)[2];


            // Change the values in the array to 1 (on) or 0 (off)
            // depending on the given input
            if (mev->isNoteOn() == 1) {
                MidiFileArray[currentTick][pitchValue] = 1;
            } else if (mev->isNoteOff() == 1){
                MidiFileArray[currentTick][pitchValue] = 0;
            }

        } else {

            // If the midievent tick is higher than out current tick value, we should copy
            // the previous array/eventlist until the ticks are even 
            while (currentTick < tickValue){
                for (int i = 0; i < 127; i++){
                    MidiFileArray[currentTick + 1][i] = MidiFileArray[currentTick][i];
                }
                currentTick++;
            }
            // reset the midi event with the correct tick value 
            event--;
        }
   }
}


