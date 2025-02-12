#include <Wire.h>
#include "SparkFunBME280.h"

BME280 envSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("BME280 test");

  Wire.begin();

  envSensor.setI2CAddress(0x76);  // Define I2C address
  if (envSensor.beginI2C() == false) {
    Serial.println("Error: Could not find a BME280 sensor!");
    while(1);
  }
}

void loop()
{
  Serial.print("Humidity: ");
  Serial.print(envSensor.readFloatHumidity(), 0);
  Serial.print(" %");

  Serial.print(" Pressure: ");
  Serial.print(envSensor.readFloatPressure() / 100.0F, 0);
  Serial.print(" hPa");

  Serial.print(" Temp: ");
  Serial.print(envSensor.readTempC(), 2);
  Serial.println(" °C");

  delay(200);
}
