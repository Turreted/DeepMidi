import subprocess
import logging
from deepmidi.definitions import *
import os

def decode_midi_file(infile: str, outfile: str):
    """
    Python wrapper to call C++ binary midiDecoder, 
    which converts a midi file serialized as a numpy 
    array to a midi file 

    Parameters
    ----------
    infile:
        Input .npy file
    outfile:
        Output .midi file
    """

    instream = open(infile, 'rb').read()
    magic_bytes = instream[:6]

    # check file extension
    if infile[infile.rfind("."):] != ".npy":
        logging.warning("File should have extension .npy")

    # validate midi file by checking magic bytes
    if "NUMPY" not in magic_bytes.decode("ISO-8859-1"):
        logging.error("Input file must be a numpy file")
        return

    try:
        subprocess.run([DECODER_BINARY, infile, outfile], check=True)
    except subprocess.CalledProcessError as e:
        logging.exception("Binary improperly envoked")
