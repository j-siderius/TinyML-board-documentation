#include <Wire.h>
#include "SparkFun_BMI270_Arduino_Library.h"

BMI270 imuSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("BMI270 test");

  Wire.begin();

  if (imuSensor.beginI2C(0x69) != BMI2_OK) {
    Serial.println("Error: Could not find a BMI270 sensor!");
    while (1);
  }
}

void loop()
{
    imuSensor.getSensorData();

    // Print acceleration data
    Serial.print("Acceleration in g's");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imuSensor.data.accelX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imuSensor.data.accelY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.print(imuSensor.data.accelZ, 3);

    Serial.print("\t");

    // Print rotation data
    Serial.print("Rotation in deg/sec");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imuSensor.data.gyroX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imuSensor.data.gyroY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.println(imuSensor.data.gyroZ, 3);

    delay(50);
}
