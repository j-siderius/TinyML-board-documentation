#define pin_button1 0
#define pin_button2 47

void setup() {
    Serial.begin(9600);

    Serial.println("Button Test");
    pinMode(pin_button1, INPUT_PULLUP);
    pinMode(pin_button2, INPUT_PULLUP);
}

void loop() {
    if (!digitalRead(pin_button1)) {
        int sum = 0;
        for (int i = 0; i < 8; i++) {
            sum += !digitalRead(pin_button1);
        }
        if (sum == 8) {
            Serial.println("Button 1 was pressed!");
        }
    }

    if (!digitalRead(pin_button2)) {
        int sum = 0;
        for (int i = 0; i < 8; i++) {
            sum += !digitalRead(pin_button2);
        }
        if (sum == 8) {
            Serial.println("Button 2 was pressed!");
        }
    }
}
