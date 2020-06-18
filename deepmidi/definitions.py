import os
import pathlib

# directory constants
CURRENT_FILE = os.path.abspath(__file__)
PROJECT_DIR = pathlib.Path(CURRENT_FILE).parent
ROOT_DIR = pathlib.Path(PROJECT_DIR).parent

# Binary paths
ENCODER_BINARY = os.path.join(ROOT_DIR, "encoding/bin/midiEncoder")
DECODER_BINARY = os.path.join(ROOT_DIR, "encoding/bin/midiDecoder")
