#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( ib06_gp ) {
    0,   0, 14,  6,
    0,   8,  8,  3,
    0,  51, 88, 27,
    0,  30, 66, 33,
    5,  28, 63, 31,
   38,   1, 28,  4,
   79,   4, 44, 12,
  101,  39,122, 75,
  130,   0, 30,  9,
  158,  50,127,115,
  178,   1, 50, 21,
  188,  24, 70, 51,
  211,   1,  4,  1,
  219,   0, 44,  8,
  242,  39,122, 75,
  255,   1, 18,  7};

CRGBPalette16 currentPalette = ib06_gp;
#define currentBlending LINEARBLEND

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(4.5, 1000);
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
