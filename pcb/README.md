# Circuit Board documentation

This folder contains the circuit board files and schematics.

The PCB was setup and designed in [KiCad 7](https://www.kicad.org/).

Boards were manufactured and assembled by [Eurocircuits](https://www.eurocircuits.com/) in Belgium.

## Pin layout

The pin layout of the ESP32S3 is as follows:

| Pin | Connection |
|---|---|
| IO0 | Button 1 / Upload |
| IO1 | Analog 1 |
| IO2 | Analog 2 |
| IO3 | Analog 3 |
| IO4 | Analog 4 |
| IO5 | I2S SD |
| IO6 | I2S WS |
| IO7 | I2S SCK|
| IO8 | I2C SDA |
| IO9 | I2C SCL |
| IO10 | Hall Effect sensor |
| IO11 | SPI MOSI / Digital 2 |
| IO12 | SPI SCK / Digital 3 |
| IO13 | SPI MISO / Digital 4 |
| IO14 | SPI CS / Digital 1 |
| IO17 | LED |
| IO18 | Neopixels |
| IO19 | USB D- |
| IO20 | USB D+ |
| IO21 | IMU wake interrupt |
| IO47 | Button 2 |
| TXD0 | TX |
| RXD0 | RX |

## I2C addresses

The sensors are connected with the following I2C addresses:

- **BMI270** - 0x69
- **BME280** - 0x76
- **VL53L0X** - 0x29

<br>

&copy; Jannick Siderius
