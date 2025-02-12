#include <Wire.h>
#include <VL53L0X.h>

VL53L0X vl53Sensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("VL53L0X test");

  Wire.begin();

  vl53Sensor.setTimeout(500);
  if (!vl53Sensor.init()) {
    Serial.println("Error: Could not find a VL53L0X sensor!");
    while (1);
  }

  vl53Sensor.startContinuous();  // Start continuous back-to-back mode
}

void loop()
{
  Serial.print(vl53Sensor.readRangeContinuousMillimeters());
  Serial.println(" mm");

  delay(50);
}
