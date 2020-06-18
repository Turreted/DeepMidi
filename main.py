import os
from deepmidi.definitions import *
from deepmidi.data.decode import decode_midi_file
from deepmidi.data.encode import encode_midi_file

def main():
    encode_midi_file("deepmidi/data/test.midi", "test.npy")
    decode_midi_file("test.npy", "final.midi")



if __name__ == '__main__':
    main()