# TensorFlow Lite Micro - LSTM example

Running a LSTM model on the TinyML board using TensorFlow Lite Micro involves some specific steps. The newest TensorFlow version (2.16.1 as of April 2023) does not correctly implement the TensorFlow Lite converter to support LSTM layers.

In order to build a TensorFlow Lite Micro model with LSTM layers, a older version of TensorFlow needs to be used (tested on 2.15.0). This requires Python 3.10.x to run. To make this requirement easier to follow, a Google Colab notebook has been setup to use as a starting point. The notebook can be found here [![Open In Colab](/assets/images/colab-badge.svg)](https://colab.research.google.com/drive/1QOhNCvtm9pPYMPuG1glV9HPyhMwgM2Lw?usp=sharing).

You can find an example Arduino sketch that uses the LSTM C-array model in the folder [TinyML-board-TensorFlowLiteMicro-LSTM-example](./tinyml-board-tensorflowlitemicro-lstm-example/).

The TensorFlow Lite Micro version in this repository supports the default TensorFlow Keras LSTM layer, like in the example below:

```python
model = tf.keras.models.Sequential([
    tf.keras.layers.Input(shape=x_train[0].shape, name="input"),
    tf.keras.layers.LSTM(20, return_sequences=True),
    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(10, activation="softmax", name="output")
])
```

The converted code would result in the following model:

![LSTM model structure in TensorFlow Lite](/assets/images/lstm_model_tflite.png)

---

The underlying logic that needs to be implemented in order to convert a TensorFlow LSTM layer into a TensorFlow Lite-compatible layer revolves around the need for fixed input and output shapes. In line with the [TensorFlow standard for RNN conversion](https://www.tensorflow.org/lite/models/convert/rnn#keras_lstm_conversion_recommended), the model is locked into a state where the dimension 0 of the input tensor is the batch size (usually 1) and the the subsequent dimensions are the shape of a dataframe. By locking these shapes, TensorFlow Lite is able to assign fixed size input and output tensors to the model, which is nescessary in order to deploy the model to an edge device. After locking the shapes, the model can be converted using the normal TensorFlow Lite Converter as described in the [TensorFlow Lite Converter documentation](https://www.tensorflow.org/lite/models/convert/convert_models).