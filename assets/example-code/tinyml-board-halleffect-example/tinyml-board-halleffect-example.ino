#define pin_hall_eff 10

void setup() {
    Serial.begin(115200);
    Serial.println("Hall Effect Test");
    
    pinMode(pin_hall_eff, INPUT);
}

void loop() {
    analogRead(pin_hall_eff);
    char buffer[50];
    sprintf(buffer, "%f mV", 3.3 * analogRead(pin_hall_eff) / 4095);
    Serial.println(buffer);
    delay(100);
}