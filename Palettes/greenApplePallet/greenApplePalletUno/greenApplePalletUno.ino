#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

DEFINE_GRADIENT_PALETTE( apple_green_gp ) {
    0,  83,235,  1,
   25,  83,235,  1,
   25,  38,197,  1,
   51,  38,197,  1,
   51,  15,161,  1,
   76,  15,161,  1,
   76,   5,130,  1,
  102,   5,130,  1,
  102,   1,103,  1,
  127,   1,103,  1,
  127,   1, 79,  4,
  153,   1, 79,  4,
  153,   1, 57,  7,
  178,   1, 57,  7,
  178,   1, 40,  9,
  204,   1, 40,  9,
  204,   1, 27,  9,
  229,   1, 27,  9,
  229,   1, 15,  7,
  255,   1, 15,  7};



CRGBPalette16 currentPalette = apple_green_gp;
#define currentBlending LINEARBLEND

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
}


void loop(){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
