# TensorFlow Lite Micro - LSTM example

Running a LSTM model on the TinyML board using TensorFlow Lite Micro involves some specific steps. The newest TensorFlow version (2.16.1 as of April 2023) does not correctly implement the TensorFlow Lite converter to support LSTM layers.

In order to build a TensorFlow Lite Micro model with LSTM layers, a older version of TensorFlow needs to be used (tested on 2.15.0). This requires Python 3.10.x to run. To make this requirement easier to follow, a Google Colab notebook has been setup to use as a starting point. The notebook can be found here [![Open In Colab](../assets/images/colab-badge.svg)](https://colab.research.google.com/drive/1QOhNCvtm9pPYMPuG1glV9HPyhMwgM2Lw?usp=sharing).

The TensorFlow Lite Micro version in this repository supports the default TensorFlow Keras LSTM layer, like in the example below:

```python
model = tf.keras.models.Sequential([
    tf.keras.layers.Input(shape=x_train[0].shape, name="input"),
    tf.keras.layers.LSTM(20, return_sequences=True),
    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(10, activation="softmax", name="output")
])
```

You can find an example Arduino sketch that uses the generated C-array model in this folder.