import subprocess
import logging
from deepmidi.definitions import *
import os

def encode_midi_file(infile: str, outfile: str):
    """
    Python wrapper to call C++ binary midiEncoder, 
    which serializes a midi file as a numpy array 

    Parameters
    ----------
    infile
        Input .midi file
    outfile:
        Output .npy file
    """

    instream = open(infile, 'rb').read()
    magic_bytes = instream[:4]

    # check file extension
    if infile[infile.rfind("."):] not in [".mid", ".midi"]:
        logging.warning("File should have extension .midi or .mid")

    # validate midi file by checking magic bytes
    if "MThd" not in magic_bytes.decode("ISO-8859-1"):
        logging.error("Input file must be a midi file")
        return

    try:
        subprocess.run([ENCODER_BINARY, infile, outfile], check=True)
    except subprocess.CalledProcessError as e:
        logging.exception("Binary improperly envoked")
