import os
import numpy as np
from numpy.matrixlib.defmatrix import matrix

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import tensorflow as tf

batch_size = 1
time_steps = 2
layer_num = 2
hidden_size = 2

model = tf.keras.Sequential()
for _ in range(layer_num - 1):
    model.add(tf.keras.layers.LSTM(hidden_size, return_sequences=True, bias_initializer="ones"))
model.add(tf.keras.layers.LSTM(hidden_size, return_sequences=False, bias_initializer="ones"))
input = np.random.random((batch_size, time_steps, hidden_size)).astype(np.float32)
output = model(input).numpy()

size = [batch_size, time_steps, layer_num, hidden_size]
W = []
U = []
bias = []
for i in range(layer_num):
    layer = model.get_layer(index=i)
    weights = layer.get_weights()
    W.append(weights[0])
    U.append(weights[1])
    bias.append(weights[2])
size = np.array(size, dtype=np.uint32)
W = np.array(W)
U = np.array(U)
bias = np.array(bias)

size.tofile(os.path.join(os.path.dirname(__file__), "size.bin"))
W.tofile(os.path.join(os.path.dirname(__file__), "W.bin"))
U.tofile(os.path.join(os.path.dirname(__file__), "U.bin"))
bias.tofile(os.path.join(os.path.dirname(__file__), "bias.bin"))
input.tofile(os.path.join(os.path.dirname(__file__), "input.bin"))
output.tofile(os.path.join(os.path.dirname(__file__), "output.bin"))
