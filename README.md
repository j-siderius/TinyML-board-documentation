# TinyML Board Documentation

![Board version: 2.1](assets/images/version21.svg)

The TinyML board is a development board specifically tailored to the exploration of TinyML concepts and to test possible applications of TinyML in an easy way. It features a powerfull microcontroller as well as a suite of sensors to sense the environment. Combined with a special TensorFlow Lite Micro library, it is easy to use this devide and start deploying machine learning models to the Edge.
<!-- This repository documents the functionality and usage of the TinyML Board. Use the contents header below to navigate to information about the hardware, software, setup, examples and more. -->

<div align="center">
    <img src="assets/images/tinyml-board-v21.png" alt="TinyML board" width="50%" height="auto" alt="Closeup of the TinyML board, showing the top side of the circuitboard.">
</div>

## Contents
- [Quick start](#quick-start)
- [Hardware](#hardware)
  - [Sensors](#sensors)
  - [Processor](#processor)
  - [Input/Output](#inputoutput)
  - [Expansion headers](#expansion-headers)
- [Software](#software)
  - [Arduino](#arduino-ide)
  - [IDE configuration](#ide-configuration)
  - [Serial Port Setup](#serial-port-setup)
  - [Libraries](#arduino-libraries)
  - [TensorFlow Lite Micro library](#tensorflow-lite-micro-library)
  - [Uploading code](#uploading-code)
- [Code examples](#code-examples)
  - [Sensor examples](#sensor-examples)
  - [I/O examples](#io-examples)
  - [TensorFlow Lite Micro examples](#tensorflow-lite-micro-examples)
  - [Board tests](#board-tests)
- [Frequently Encountered Issues](#frequently-encountered-issues)
- [License](#license-and-contact)

## Quick start

 1. Install the ESP32 board support into Arduino IDE by adding the Espressif repository to the Board Manager and then downloading the ESP32 boards - [Espressif Arduino ESP32 installation](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide).
 2. Install libraries for the sensors ([Sparkfun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library), [Sparkfun BMI270](https://github.com/sparkfun/SparkFun_BMI270_Arduino_Library), [Pololu VL53L0X](https://github.com/pololu/vl53l0x-arduino) and [FastLED](https://github.com/FastLED/FastLED)) using the Library Manager and TensorFlow Lite Micro ([TFLiteMicro_ArduinoESP32S3](https://github.com/j-siderius/TFLiteMicro_ArduinoESP32S3)) from the GitHub page.
 3. Choose an [example project](#code-examples) for the TinyML board and load the code into Arduino IDE.
 4. Press and hold the `Upload/Btn1` button, then press the `RESET` button. Release all buttons and click `Upload`, then wait for the code to upload.
 5. Check the Serial Monitor or Serial Plotter in Arduino IDE to see the output from the model.

More detailed instructions can be found in the corresponding sections below.

[🔼 Back to the top](#tinyml-board-documentation)

## Hardware

The TinyML board contains several sensors and a powerfull processor to get up and running with TinyML quickly. In the following sections, a general overview as well as technical details on all hardware can be found.

<div align="center">
    <img src="assets/images/tinyml-board-annotated.png" alt="TinyML board annotated" alt="Overview of the TinyML board, annotated with lines and text describing the location of all sensors, inputs and outputs as well as the microcontroller.">
</div>

### Sensors

The TinyML board contains five different sensors that can be used for gathering data. To see how to use the sensors, look at the [Code Examples](#code-examples).

- **Microphone (I2S)** [_ICS-43434_](assets/datasheets/ics43434.pdf) - This sensor measures the amplitude and pitch of sound.
- **Time-of-Flight range sensor** [_VL53L0X_](assets/datasheets/vl53l0x.pdf) - This sensor measures short-range distance.
- **Environmental sensor** [_BME280_](assets/datasheets/bme280.pdf) - This sensor measures temperature, relative humidity and atmospheric pressure.
- **Hall effect magnet sensor** [_AH49E_](assets/datasheets/ah49e.pdf) - This sensor measures the magnetic field around its axis.
- **Inertial Measurement Unit (IMU)** [_BMI270_](assets/datasheets/bmi270.pdf) - This sensor measures both the angular motion using a gyroscope, as well as the acceleration using an accelerometer.

### Processor

The TinyML board is fitted with an ESP32-S3 SoC. The processor features a fast 240MHz, dual-core processor, large 16MB storage and 8MB RAM. 
Additionally, it has Bluetooth 5 and WiFi capabilities, making it easy to connect the TinyML board to the internet, for example to share sensor data.
More information about the onboard chip can be found in the datasheet: [ESP-S3-WROOM1-N16R8](assets/datasheets/esp32s3wroom1.pdf).

### Input/Output

Besides sensors, the TinyML board also contains multiple Inputs and Outputs (I/O). To see how to use the I/O, look at the [Code Examples](#code-examples).

- **Buttons** - Two buttons are accessible to the user (`Upload/Btn1` and `Btn2`), which can be user-configured. Both buttons need to be pulled high by the processor (see the [Code Examples](#code-examples)).
  The last button (`RESET`) is used if the board needs to be programmed or debugged, e.g. if the TinyML board or the application need to be restarted.
- **Output LED** - The red LED can be used as simple output, e.g. for showing if a sensor functions properly. The output LED is marked `LED` on the TinyML board.
- **Neopixels** - The Neopixel LEDs can be addressed individually to display RGB colors. They can output application information, give users feedback and more. The Neopixels are marked `Neopixels` on the TinyML board.

- **USB-C connector** - This connector is primarily used for programming and serial communication with the TinyML board. It is also the primary power input for the board. To program the board, a USB-C _Data_ cable is needed.
- **Stemma QT / QWIIC** - This connector enables users to connect extra sensors, making the TinyML board suitable for even more advanced projects.
  The connector uses the popular [Adafruit Stemma QT](https://www.adafruit.com/category/620) and [SparkFun QWIIC](https://www.sparkfun.com/categories/399) standards, opening up the possibilty for many extra sensors.
  Using a Stemma QT expansion board, users can connect even more sensors in series. For the pinout, refer to the [Expansion headers](#expansion-headers) section. This connector if marked `Stemma QT/QWIIC` on the TinyML board.
- **Expansion header** - This connector can be used to connect extra peripherals, sensors, actuators and more to adapt the TinyML board to different projects. This connector is marked `Expansion Header` on the TinyML board.
  The connector features power, digital and analog connections, as well as support for the SPI high-speed databus. In combination with the ESP32S3's built in GPIO multiplexer, the connector gives the freedom to connect many different things to the TinyML board.
  For the pinout, refer to the [Expansion headers](#expansion-headers) section.

- **Miscellaneous** - The TinyML board also contains some other, miscellaneous component.
  These components are used to show power (green LED, marked `ON` on the TinyML board), convert voltage, debug the TinyML board (header, marked `Debugging` on the TinyML board) and some other passive components. Additionally, the board features some test-points (2x GND, VUSB, 3.3V and IO0) which can be used to verify the functionality of some components.

### Expansion headers

Below a systematic overview of all expansion headers present on the TinyML board is shown. The Expansion header features four analog GPIO pins (A1 - A4 in the top row), four digital GPIO pins (D1 - D4 in the bottom row), as well as 3.3V power and ground (GND). The digital GPIO pins also expose the SPI data bus of the ESP32S3 microcontroller as follows:

| GPIO pin | Description |
| --- | --- |
| D1 / GPIO14 | SPI CS |
| D2 / GPIO11 | SPI MOSI |
| D3 / GPIO12 | SPI SCK |
| D4 / GPIO13 | SPI MISO |

The TinyML board can technically be powered through the Expansion Header, but the power should be stable and noise-free **3.3V** only. If the external power is fluctuating, the microcontroller could be damaged. If it is absolutely nescessary to provide variable external power from another source than USB-C (e.g. from a battery), it is possible to utilise the testpoints GND and VUSB close to the USB-C connector on the board. The VUSB testpoint routes the power through the on-board voltage regulator first, which produces clean 3.3V.

For detailed information about the circuit board, refer to the [Circuit board documentation](/pcb/README.md).

<div align="center">
    <img src="assets/images/tinyml-board-expansion-annotated.png" alt="TinyML board headers annotated">
</div></div>

[🔼 Back to the top](#tinyml-board-documentation)

## Software

In order to use the TinyML board, it needs to be correctly setup. The TinyML board requires no hardware setup, but it does require some software setup. In order to start using it, connect a USB-C _Data_ cable to the board and plug it into a free USB port on the system. Below sections detail the setup of the Arduino IDE, installation of sensor libraries and finally the TensorFlow Lite Micro setup.

### Arduino IDE

The TinyML board can be programmed using the [Arduino IDE](https://www.arduino.cc/en/software), both the new 2.x and Legacy >1.8 versions.
Please make sure that the Arduino IDE is installed on the system before continuing.

In order to program the TinyML board, the [ESP32](#processor) platform need to be installed. To do this, follow the steps below:

1. Open the Arduino IDE and navigate to the `Preferences` (_Windows_: File > Preferences, _Mac_: Arduino > Preferences), as shown in the left image below.
2. In the field `Additional boards manager URLs:` enter the following link (If there are already other URLs in this field,
   open the full list by clicking the folder icon to the right of the URL):
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```   
3. Press `Ok` to close the `Preferences`.
4. Open the `Boards Manager` by going to Tools > Boards > Boards Manager.
5. Search for **ESP32** and install the platform by Espressif Systems.
6. Restart the Arduino IDE.

<div align="center">
    <img src="assets/images/arduino-preferences.png" alt="Arduino Preferences menu" width="45%">
    <img src="assets/images/arduino-boards-manager.png" alt="Arduino Boards Manager" width="45%">
</div>

For more advanced installations, for example in Platform IO, follow this [advanced installation guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

### IDE configuration

In order to use all functions that the ESP32S3 processor has, Arduino IDE must be properly configured when programming the TinyML board. Below are the most important settings, these need to be configured in the `Tools menu` (_Windows_ + _Mac_: Tools) by clicking on the setting and choosing the correct option:

- **Board** - *ESP32S3 Dev Module*: This sets the correct processor and board configuration for the TinyML board. To select the ESP32 Dev Module, first select the *esp* platform.
- **Port** - *port here*: Enter the serial port of the TinyML board here. Refer to the guide [Serial Port](#serial-port-setup) to find this port.
- **USB CDC On Boot** - *Enabled*: This setting enables the onboard USB-C port to be used for serial communication.
- **Flash mode** - *DIO 80MHz*: This setting configures the correct mode for writing to the flash of the ESP32S3.
- **Flash Size** - *16MB (128Mb)*: This setting uses the full storage of the ESP32S3, enabling space for larger projects and more code.
- **PSRAM** - *OPI PSRAM*: This setting enables the fast built-in RAM of the ESP32S3.

<div align="center">
    <img src="assets/images/arduino-programming-settings.png" alt="Arduino Board settings">
</div>

### Serial Port setup

No drivers are required for the TinyML board. However, sometimes, it is nescessary to know on which serial port the TinyML board is connected. To find this out, perform the following steps:

_Arduino IDE_
1. Open the `Port overview menu` (_Windows_ + _Mac_: Tools > Port) and observe which ports are in the list. 
2. Close the list.
3. Plug in the TinyML board and open the `Port overview menu`, observe which port was added to the list > this is the TinyML board port.

If the above method does not work, an OS-specific check can be done using the instructions below:

_Windows_
1. Open `Device Manager` by going to Start and searching for the program. (Alternatively, press the <kbd>![Windows Key](assets/images/winlogo.png)</kbd> key and search for Device Manager)
2. Open the `Ports (COM & LPT)` section.
3. Plug in the TinyML board and observe which COM port was added to this list > this is the TinyML board port.

_Mac_
1. Open the `Terminal` application by going to Applications > Utilities. (Alternatively, press the <kbd>![CMD Key](assets/images/cmdlogo.png) + Spacebar</kbd> keys and search for Terminal)
2. Enter the following command `ls /dev/tty*` and press <kbd>Enter</kbd>.
3. Plug in the TinyML board and repeat step 2, observe which port was added to the list > this is the TinyML board port.

### Arduino libraries

In order to use the sensors on the TinyML board, some Arduino libraries are needed. The recommended libraries are listed below, although other libraries might work as well.

The libraries can be installed into Arduino IDE through the Library Manager (Sketch > Include Library > Manage Libraries). The versions are included here for documentation purpose, the newest version of each library should work fine.

- [Sparkfun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library) (2.0.10)
- [SparkFun BMI270](https://github.com/sparkfun/SparkFun_BMI270_Arduino_Library) (1.0.3)
- [Pololu VL53L0X](https://github.com/pololu/vl53l0x-arduino) (1.3.1)
- [FastLED](https://github.com/FastLED/FastLED) (3.9.13)

The onboard [Microphone](#sensors) uses the built-in I2S library from Espressif, so there is no library to install to use the microphone. More information can be found in the [I2S Peripherals documentation](https://docs.espressif.com/projects/esp-idf/en/v3.3/api-reference/peripherals/i2s.html). 

### TensorFlow Lite Micro library

<span style="color:red">**TODO:**</span> Add new library references here

<!-- In order to run TensorFlow models on the TinyML board, the TensorFlow Lite Micro library needs to be setup properly. 
Included in this repository is a TensorFlow Lite Micro library specifically tailored to the ESP32 processor on the TinyML board.

The library can be downloaded as ZIP from this repository: [![Download Arduino_TensorFlowLite_ESP32](assets/images/arduino-tflite-esp32-download.svg)](/arduino-tensorflowlite-esp32/Arduino_TensorFlowLite_ESP32.zip)

To install the library, follow the steps below:

1. Download the library ZIP file from the link above.
2. Open the Arduino IDE and navigate to the **Include Library** menu. (Windows + Mac: Sketch>Include Library)
3. Click on <kbd>Add .ZIP Library...</kbd>.
4. In the file window that opens, navigate to the location where the ZIP file was downloaded.
5. Select the ZIP file and click <kbd>Open</kbd>. Wait for the Installation to finish.

<div align="center">
    <img src="assets/images/arduino-install-ziplibrary.png" alt="Install ZIP library in Arduino IDE">
</div>

Not all normal TensorFlow Ops (layers) are supported by TensorFlow Lite Micro. In order to see what operations the TensorFlow model uses, you can upload your saved model to [Netron](https://netron.app/) and examine it. The supported operations in this version of TensorFlow Lite Micro can be found in the [Arduino-TensorFlowLite-ESP32 README](/arduino-tensorflowlite-esp32/README.md#supported-ops).

A special thanks to [Nikos Kouvaris](https://github.com/nkoub) and [Tanaka Masayuki](https://github.com/tanakamasayuki) for porting the [original Arduino_TensorFlowLite_ESP32 library](https://github.com/nkoub/Arduino_TensorFlowLite_ESP32)

> [!IMPORTANT]
> The TensorFlow Lite Micro ESP32 library included in this repository works with the TensorFlow Lite Micro release from Feb 2023.
> With much manual modifications, the library can be updated, however there is no compatibility guarantee as much of the TensorFlow Lite Micro codebase has changed without proper notice and documentation. -->

### Uploading code

To upload a program to the TinyML board, follow the steps below:

1. Connect the TinyML board to the system using a USB-C cable.
2. Ensure that the IDE settings are setup as described in the [Arduino IDE](#arduino-ide) and [IDE configuration](#ide-configuration) sections.
3. Select the correct serial port for the TinyML board, as described in the [Serial Port setup](#serial-port-setup) section.
4. Press and hold the `Upload/Btn1` button, then press the `RESET` button. This puts the ESP32S3 into *Upload*\* mode.
5. Release all buttons and click `Upload`, then wait for the code to upload.

\* Technically, this mode is called *Download*, since the code is downloaded to the microcontroller, but for ambiguities sake, it is called *Upload* here.

[🔼 Back to the top](#tinyml-board-documentation)

## Code examples

Example code for all described functions of the TinyML board can be found below. They are divided into sensors, I/O and TensorFlow Lite Micro examples.

The TinyML board usually comes pre-programmed with a Board Test firmware. This program tests all functionality of the TinyML board. To start the test, just connect the TinyML board to the system and open the Serial Monitor in Arduino IDE (_Windows_ + _Mac_: either through GUI button or Tools > Serial Monitor).

Additional (advanced) examples can be found in the [ESP32 Arduino library documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html).

### Sensor examples

<span style="color:red">**TODO:**</span> New library examples here

- Microphone [![Open In Github](assets/images/github-badge.svg)](assets/example-code/tinyml-board-microphone-example/)
<!-- - Time-of-Flight sensor [![Open In Github](assets/images/github-badge.svg)](assets/example-code/tinyml-board-tof-example/) -->
<!-- - Environmental sensor [![Open In Github](assets/images/github-badge.svg)](assets/example-code/tinyml-board-environmental-example/) -->
- Hall-effect magnetic sensor [![Open In Github](assets/images/github-badge.svg)](assets/example-code/tinyml-board-halleffect-example/)
<!-- - Inertial Measurement Unit (IMU) [![Open In Github](assets/images/github-badge.svg)](assets/example-code/tinyml-board-imu-example/) -->

### I/O examples

- Buttons [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-buttons-example/)
- LED [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-led-example/)
- Neopixels [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-neopixel-example/)
- Expansion header [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-expansion-example/)

### TensorFlow Lite Micro examples

<span style="color:red">**TODO:**</span> New library examples here

<!-- - TensorFlow Lite Micro sine example [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-tensorflowlitemicro-example/) -->
<!-- - TensorFlow Lite Micro LSTM example [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-tensorflowlitemicro-lstm/) -->

### Board tests

<span style="color:red">**TODO:**</span> Fix library dependencies

- TinyML Board Test [![Open In Github](assets/images/github-badge.svg)](/assets/example-code/tinyml-board-tests/)

## Frequently Encountered Issues

<span style="color:red">**TODO:**</span> Explain frequently encountered issues here

- Cannot see TinyML board serial port > USB-C data cable
- Cannot set ESP32 settings > install ESP32 board definitions
- Cannot upload code to the TinyML board > download mode
- Compiling code fails library > missing library
- Compiling code fails size > reduce size e.g. bytearrays
- Compiling code fails unsupported ops > check ops using TFLite checker
- No output after upload > USB CDC + port
- Crashing output after upload > check code errors
- No sensor output / failing sensor init > check i2c addresses
- No button presses > enable pull-ups

[🔼 Back to the top](#tinyml-board-documentation)

## License

<span style="color:red">**TODO:**</span> Add license information here

<br>

[🔼 Back to the top](#tinyml-board-documentation)

&copy; Jannick Siderius
