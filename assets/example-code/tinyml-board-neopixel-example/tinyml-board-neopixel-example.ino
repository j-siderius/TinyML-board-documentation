#include <FastLED.h>

#define pin_neopixel 18

#define NUM_LEDS 5
CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<NEOPIXEL, pin_neopixel>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
}

void loop() {
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
}