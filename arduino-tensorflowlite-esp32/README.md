# Arduino TensorFlow Lite for ESP32

Pre-zipped Arduino_TensorFlowLite_ESP32 library. Unchanged download from [https://github.com/nkoub/Arduino_TensorFlowLite_ESP32](https://github.com/nkoub/Arduino_TensorFlowLite_ESP32).

> [!IMPORTANT]
> The TensorFlow Lite Micro ESP32 library included in this repository works with the TensorFlow Lite Micro release from Feb 2023.
> With much manual modifications, the library can be updated, however there is no compatibility guarantee as much of the TensorFlow Lite Micro codebase has changed without proper notice and documentation.

A special thanks to [Nikos Kouvaris](https://github.com/nkoub) and [Tanaka Masayuki](https://github.com/tanakamasayuki) for porting the [original Arduino_TensorFlowLite_ESP32 library](https://github.com/nkoub/Arduino_TensorFlowLite_ESP32)


## Supported Ops

The following TensorFlow Operations are (likely) supported by this TensorFlow Lite Micro port:

|Operation|
|---|
|Abs|
|Add|
|AddN|
|ArgMax|
|ArgMin|
|AssignVariable|
|BatchToSpaceNd|
|BroadcastArgs|
|BroadcastTo|
|CallOnce|
|Cast|
|Ceil|
|CircularBuffer|
|Concatenation|
|Cos|
|CumSum|
|DepthToSpace|
|Dequantize|
|DetectionPostprocess|
|Div|
|Elu|
|Equal|
|EthosU|
|Exp|
|ExpandDims|
|Fill|
|Floor|
|FloorDiv|
|FloorMod|
|Gather|
|GatherNd|
|Greater|
|GreaterEqual|
|HardSwish|
|If|
|L2Normalization|
|L2Pool2D|
|LeakyRelu|
|Less|
|LessEqual|
|Log|
|LogicalAnd|
|LogicalNot|
|LogicalOr|
|Logistic|
|LogSoftmax|
|Maximum|
|MirrorPad|
|Mean|
|Minimum|
|Neg|
|NotEqual|
|Pack|
|PadV2|
|Prelu|
|Quantize|
|ReadVariable|
|ReduceMax|
|Relu|
|Relu6|
|Reshape|
|ResizeBilinear|
|ResizeNearestNeighbor|
|Round|
|Rsqrt|
|SelectV2|
|Shape|
|Sin|
|Slice|
|Softmax|
|SpaceToBatchNd|
|SpaceToDepth|
|Split|
|SplitV|
|Squeeze|
|Sqrt|
|Square|
|SquaredDifference|
|StridedSlice|
|Sub|
|Sum|
|Tanh|
|TransposeConv|
|Transpose|
|Unpack|
|UnidirectionalSequenceLSTM|
|VarHandle|
|While|
|ZerosLike|
