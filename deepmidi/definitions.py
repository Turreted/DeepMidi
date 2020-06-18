import os
import pathlib

CURRENT_FILE = os.path.abspath(__file__)
PROJECT_DIR = pathlib.Path(CURRENT_FILE).parent
ROOT_DIR = pathlib.Path(PROJECT_DIR).parent
