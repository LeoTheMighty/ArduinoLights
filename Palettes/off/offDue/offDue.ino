#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();
    leds[0] = CRGB::Black;
    FastLED.show();
}


void loop(){
}
