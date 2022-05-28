#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( starrynite_gp ) {
    0,   4,  6, 23,
    2,   4,  6, 23,
    5,   8,  5,212,
   10,  27,138,245,
   15,   8,  5,212,
   17, 239,227,  5,
   20,   8,  5,212,
   25,   8,  5,212,
   30,   7,  8, 84,
   35,   7,  8, 84,
   40, 188,180,  3,
   43,  98,103,114,
   45,   2,  1,226,
   51, 227,219,135,
   56,   7,  8, 84,
   61,  27,138,245,
   63,   4,  6, 23,
   71,   2,  1,226,
   76,   4,  6, 23,
   81, 242,227,  1,
   84,   7,  8, 84,
   89,   7,  8, 84,
   94,   2,  1,226,
   96, 227,219,135,
   99,   4,  6, 23,
  107,  12, 28,221,
  107, 242,227,  1,
  114,   2,  1,226,
  122,  12, 28,221,
  130, 227,219,135,
  135,   2,  1,226,
  142,  12,  4, 30,
  147,  12, 28,221,
  153,   2,  1,226,
  158, 242,227,  1,
  163,   2,  1,226,
  170,   7,  8, 84,
  173, 242,227,  1,
  178,   2,  1,226,
  183,   7,  8, 84,
  193,  12,  4, 30,
  196, 242,227,  1,
  204,   2,  1,226,
  211,   4,  6, 23,
  216, 188,180,  3,
  221,   2,  1,226,
  226,   7,  8, 84,
  232,   2,  1,226,
  237, 227,219,135,
  244,   2,  1,226,
  249,   4,  6, 23,
  255,  13, 29,223};

CRGBPalette16 currentPalette = starrynite_gp;
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
