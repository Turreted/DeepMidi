import tensorflow as tf
import numpy as np

data = np.load('arr1.npy')

for a in data:
    print([i for i in a])

