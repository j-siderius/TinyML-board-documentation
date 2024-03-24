#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Adafruit_VL53L0X.h"
#include "SparkFun_BMI270_Arduino_Library.h"
#include <FastLED.h>
#include <driver/i2s.h>

#define pin_button1 0
#define pin_analog1 1
#define pin_analog2 2
#define pin_analog3 3
#define pin_analog4 4
#define pin_i2s_sd 5
#define pin_i2s_ws 6
#define pin_i2s_sck 7
#define pin_i2c_sda 8
#define pin_i2c_scl 9
#define pin_hall_eff 10
#define pin_spi_mosi 11
#define pin_spi_sck 12
#define pin_spi_miso 13
#define pin_spi_cs 14
#define pin_led 17
#define pin_neopixel 18
#define pin_imu_wake 21
#define pin_button2 47

Adafruit_BME280 bme;  // I2C
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
BMI270 imu;
// uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;  // 0x68
uint8_t i2cAddress = BMI2_I2C_SEC_ADDR;  // 0x69
#define NUM_LEDS 5
CRGB leds[NUM_LEDS];
#define SAMPLE_BUFFER_SIZE 512
#define SAMPLE_RATE 8000
#define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT
i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
  .sample_rate = SAMPLE_RATE,
  .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
  .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
  .communication_format = I2S_COMM_FORMAT_I2S,
  .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  .dma_buf_count = 4,
  .dma_buf_len = 1024,
  .use_apll = false,
  .tx_desc_auto_clear = false,
  .fixed_mclk = 0
};
i2s_pin_config_t i2s_mic_pins = {
  .bck_io_num = pin_i2s_sck,
  .ws_io_num = pin_i2s_ws,
  .data_out_num = I2S_PIN_NO_CHANGE,
  .data_in_num = pin_i2s_sd
};

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  delay(2000);
  Serial.println();
  Serial.println();
  Serial.println("############################");
  Serial.println("#  TinyML Board v2.1 test  #");
  Serial.println("#                          #");
  Serial.println("#                          #");
  Serial.println("#  Test all sensors and    #");
  Serial.println("#  functions of the        #");
  Serial.println("#  TinyML Board v2.1       #");
  Serial.println("#                          #");
  Serial.println("#  All instructions        #");
  Serial.println("#  will be preceded by     #");
  Serial.println("#  '***'.                  #");
  Serial.println("############################");
  Serial.println();
  delay(500);
  Serial.println("*** To Start, press ENTER");
  while (Serial.read() != '\n')
    ;

  // ---------- I2C test ----------
  // Serial.println("I2C Test");
  // Serial.println("Devices expected at 0x29, 0x69 and 0x76");
  // Wire.begin();
  // for (byte address = 1; address < 127; address++) {
  //   Wire.beginTransmission(address);
  //   byte error = Wire.endTransmission();
  //   if (error == 0) {
  //     Serial.print("I2C device found at address 0x");
  //     Serial.print(address, HEX);
  //   } else if (error == 4) {
  //     Serial.print("Unknown error at address 0x");
  //     Serial.println(address, HEX);
  //   }
  // }

  // ---------- BME280 ----------
  Serial.println();
  Serial.println("BME280 Test");
  // status = bme.begin();
  unsigned status = bme.begin(0x76, &Wire);
  if (!status) {
    Serial.println("Error: Could not find a BME280 sensor!");
  } else {
    char buffer[100];
    sprintf(buffer, "Temperature: %f C\nPressure: %f hPa\nHumidity: %f%%", bme.readTemperature(), bme.readPressure() / 100.0F, bme.readHumidity());
    Serial.println(buffer);

    Serial.println("*** Check if temperature, pressure and humidity are reasonable values");
    Serial.println("*** To Continue, press ENTER");
    while (Serial.read() != '\n')
      ;
  }

  // ---------- VL53L0X ----------
  Serial.println();
  Serial.println("VL53L0X Test");
  if (!lox.begin()) {
    Serial.println("Error: Could not find VL53L0X!");
  } else {
    Serial.println("*** Check if different distances are detected");
    Serial.println("*** To Start, press ENTER");
    Serial.println("*** Press ENTER again to quit this test");
    while (Serial.read() != '\n')
      ;
    while (Serial.read() != '\n') {
      delay(100);
      VL53L0X_RangingMeasurementData_t measure;
      lox.rangingTest(&measure, false);
      if (measure.RangeStatus != 4) {  // phase failures have incorrect data
        Serial.print(measure.RangeMilliMeter);
        Serial.println(" mm");
      } else {
        Serial.println(" out of range, move closer ");
      }
    }
  }

  // ---------- BMI270 ----------
  Serial.println();
  Serial.println("BMI270 Test");
  if (imu.beginI2C(i2cAddress) != BMI2_OK) {
    Serial.println("Error: Could not find BMI270!");
  } else {
    Serial.println("*** Check if movements are detected (these are represented by changes in acceleration (A) and rotation (G))");
    Serial.println("*** To Start, press ENTER");
    Serial.println("*** Press ENTER again to quit this test");
    while (Serial.read() != '\n')
      ;
    while (Serial.read() != '\n') {
      delay(100);
      imu.getSensorData();
      char buffer[150];
      sprintf(buffer, "AccX: %f, AccY: %f, AccZ: %f, GyrX: %f, GyrY: %f, GyrZ: %f", imu.data.accelX, imu.data.accelY, imu.data.accelZ, imu.data.gyroX, imu.data.gyroY, imu.data.gyroZ);
      Serial.println(buffer);
    }
  }

  // ---------- Neopixels ----------
  Serial.println();
  Serial.println("Neopixel Test");
  Serial.println("*** Check if each Neopixel shows colors");
  Serial.println("*** To Start, press ENTER");
  while (Serial.read() != '\n')
    ;
  FastLED.addLeds<NEOPIXEL, pin_neopixel>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB::Red;
    FastLED.show();
    delay(500);
    leds[led] = CRGB::Blue;
    FastLED.show();
    delay(500);
    leds[led] = CRGB::Green;
    FastLED.show();
    delay(500);
    leds[led] = CRGB::White;
    FastLED.show();
    delay(500);
    leds[led] = CRGB::Black;
    FastLED.show();
  }

  // ---------- LED ----------
  Serial.println();
  Serial.println("LED Test");
  Serial.println("*** Check if the on-board LED turns on");
  Serial.println("*** To Start, press ENTER");
  while (Serial.read() != '\n')
    ;
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, HIGH);
  delay(1000);
  digitalWrite(pin_led, LOW);

  // ---------- Buttons ----------
  Serial.println();
  Serial.println("Button Test");
  pinMode(pin_button1, INPUT_PULLUP);
  pinMode(pin_button2, INPUT_PULLUP);
  Serial.println("*** To Continue, Press Button 1");
  bool button_pressed = false;
  while (!button_pressed) {
    if (!digitalRead(pin_button1)) {
      int sum = 0;
      for (int i = 0; i < 8; i++) {
        sum += !digitalRead(pin_button1);
      }
      button_pressed = (sum == 8);
    }
  }
  Serial.println("*** To Continue, Press Button 2");
  button_pressed = false;
  while (!button_pressed) {
    if (!digitalRead(pin_button2)) {
      int sum = 0;
      for (int i = 0; i < 8; i++) {
        sum += !digitalRead(pin_button2);
      }
      button_pressed = (sum == 8);
    }
  }

  // ---------- Hall effect ----------
  Serial.println();
  Serial.println("Hall Effect Test");
  Serial.println("*** Check if changes in voltage by magnet are detected (if no magnet is available, skip this test)");
  Serial.println("*** To Start, press ENTER");
  Serial.println("*** Press ENTER again to quit this test");
  while (Serial.read() != '\n')
    ;
  pinMode(pin_hall_eff, INPUT);
  while (Serial.read() != '\n') {
    delay(100);
    analogRead(pin_hall_eff);
    char buffer[50];
    sprintf(buffer, "%f mV", 3.3 * analogRead(pin_hall_eff) / 4095);
    Serial.println(buffer);
  }

  // ---------- Microphone ----------
  Serial.println();
  Serial.println("Microphone Test");
  Serial.println("*** Check if changes output are detected after noise (numbers should be larger both in positive and negative)");
  Serial.println("*** If you want to check if there are noise-waves, open the Serial Plotter");
  Serial.println("*** To Start, press ENTER");
  Serial.println("*** Press ENTER again to quit this test");
  while (Serial.read() != '\n')
    ;
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
  int32_t raw_samples[SAMPLE_BUFFER_SIZE];
  while (Serial.read() != '\n') {
    size_t bytes_read = 0;
    i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
    int samples_read = bytes_read / sizeof(int32_t);
    for (int i = 0; i < samples_read; i++) {
      Serial.printf("%ld\n", raw_samples[i]);
    }
  }


  Serial.println();
  Serial.println();
  Serial.println("#######################");
  Serial.println("#  TinyML Board v2.1   #");
  Serial.println("#                      #");
  Serial.println("#  Test finished!      #");
  Serial.println("#  Have fun using the  #");
  Serial.println("#  TinyML Board v2.1!  #");
  Serial.println("########################");
  Serial.println();
  Serial.println();
}

void loop() {}
