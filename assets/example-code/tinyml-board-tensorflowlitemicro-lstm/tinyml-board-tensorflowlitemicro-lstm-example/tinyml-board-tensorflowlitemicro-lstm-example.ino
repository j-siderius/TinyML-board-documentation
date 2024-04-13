// Include necessary libraries for TensorFlow Lite
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Include the model and the data
#include "lstm_model.h"
#include "digits.h"

// Define global variables
namespace {
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

constexpr int kTensorArenaSize = 10000;  // Define the size of the tensor arena
uint8_t tensor_arena[kTensorArenaSize];  // Define the tensor arena
}  // namespace

char buffer[250];  // Buffer for storing error messages

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  delay(500);
  Serial.println("--- Starting setup");

  // Load the model
  model = tflite::GetModel(lstm_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    sprintf(buffer, "--- Model provided is schema version %d not equal to supported version %d.", model->version(), TFLITE_SCHEMA_VERSION);
    Serial.println(buffer);
    return;
  } else {
    Serial.println("--- Model loaded");
  }

  // Resolve all operation implementations needed
  static tflite::AllOpsResolver resolver;

  // Build the interpreter
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;
  Serial.println("--- Interpreter setup");

  // Allocate memory for the model's tensors
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    sprintf(buffer, "--- AllocateTensors() failed");
    Serial.println(buffer);
    return;
  } else {
    Serial.println("--- Tensors allocated");
  }

  delay(500);
  size_t used_size = interpreter->arena_used_bytes();
  Serial.print("--- Arena used bytes: ");
  Serial.println(used_size);

  // Obtain pointers to the model's input and output tensors
  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop() {
  int random_digit = random(0, 10);  // Generate a random digit

  Serial.print("\nPredicting number ");
  Serial.println(random_digit);

  float (*digit)[28][28] = digits[random_digit];  // Get the corresponding digit data

  // Fill the input tensor with the digit data
  for (int row = 0; row < 28; row++) {
    for (int column = 0; column < 28; column++) {
      int nr = (column * 28) + row;
      input->data.f[nr] = (*digit)[column][row];
    }
  }

  unsigned long startMicros = micros();  // Start timing

  // Run inference
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    Serial.println("--- Invoke() failed");
    return;
  }

  // Print the time taken for inference
  Serial.print("Invocation took ");
  Serial.print(micros() - startMicros);
  Serial.println(" micros");

  float y_predicted[10];  // Array to store the prediction results

  Serial.println("digit:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9");
  Serial.print("proba:\t");

  // Print the prediction results
  for (int i = 0; i < 10; i++) {
    y_predicted[i] = output->data.f[i];
    Serial.print(y_predicted[i], 5);
    Serial.print("\t");
  }

  delay(1000);  // Delay before the next loop
}
