import subprocess
import logging
from deepmidi.definitions import *
import os

# consider using https://github.com/ahupp/python-magic

BINARY = os.path.join(ROOT_DIR, "encoding/bin/decoder")


def encode(infile: str, outfile: str):
    instream = open(infile, 'rb').read()
    magic_bytes = instream[:4]

    # check file extension
    if infile[infile.rfind("."):] not in [".mid", ".midi"]:
        logging.warning("File should have extension .midi or .mid")

    # validate midi file by checking magic bytes
    if magic_bytes.decode('utf-8') != "MThd":
        logging.error("Input file must be a midi file")
        return
    

    subprocess.run([BINARY, infile, outfile], shell=True, check=True)


encode("deepmidi/data/test.midi", "test.npy")