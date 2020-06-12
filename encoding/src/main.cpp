#include "MidiFile.h"
#include "Options.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

   MidiFile midifile("./data/classical.midi");



   midifile.doTimeAnalysis();
   midifile.linkNotePairs();

   int tracks = midifile.getTrackCount();
   cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
   if (tracks > 1) cout << "TRACKS: " << tracks << endl;
   for (int track=0; track<tracks; track++) {
      if (tracks > 1) cout << "\nTrack " << track << endl;
      cout << "Tick\tSeconds\tDur\tMessage" << endl;
      for (int event=0; event<midifile[track].size(); event++) {
         cout << dec << midifile[track][event].tick;
         cout << '\t' << dec << midifile[track][event].seconds;
         cout << '\t';
         if (midifile[track][event].isNoteOn())
            cout << midifile[track][event].getDurationInSeconds();

         for (int i=0; i<midifile[track][event].size(); i++)
            cout << (int)midifile[track][event][i] << ' ';
         cout << endl;
      }
   }

   return 0;
}