#define pin_analog1 1
#define pin_analog2 2
#define pin_analog3 3
#define pin_analog4 4

#define pin_spi_mosi 11
#define pin_spi_sck 12
#define pin_spi_miso 13
#define pin_spi_cs 14

int analogOutput = 0;

void setup() {
    Serial.begin(115200);

    pinMode(pin_analog1, INPUT);
    pinMode(pin_analog2, INPUT);

    pinMode(pin_analog3, OUTPUT);
    pinMode(pin_analog4, OUTPUT);

    // The digital pins can also be used as SPI pins, 
    // please refer to specific SPI instructions for their use
    pinMode(pin_spi_mosi, INPUT);
    pinMode(pin_spi_sck, INPUT);
    pinMode(pin_spi_miso, INPUT);
    pinMode(pin_spi_cs, INPUT);
}

void loop() {
    Serial.print("analog1: "); Serial.println(analogRead(pin_analog1));
    Serial.print("analog2: "); Serial.println(analogRead(pin_analog2));

    analogWrite(pin_analog3, analogOutput);
    analogWrite(pin_analog4, 255 - analogOutput);
    
    if (analogOutput < 255) {
        analogOutput++;
    } else {
        analogOutput = 0;
    }

    Serial.print("digital1: "); Serial.println(digitalRead(pin_spi_mosi));
    Serial.print("digital2: "); Serial.println(digitalRead(pin_spi_sck));
    Serial.print("digital3: "); Serial.println(digitalRead(pin_spi_miso));
    Serial.print("digital4: "); Serial.println(digitalRead(pin_spi_cs));

    delay(100);
}