#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( vampirelips_gp ) {
    0,   0,  0,  0,
   17,  26, 10,  6,
   48,  90,  1,  9,
   76,  32,  1,  3,
   86,   0,  0,  0,
   96,  26, 10,  6,
  104, 140,154,133,
  107,  26, 10,  6,
  114,  90,  1,  9,
  119,   0,  0,  0,
  130,  90,  1,  9,
  137,  26, 10,  6,
  142,  26, 10,  6,
  145, 140,154,133,
  150,   0,  0,  0,
  170,  32,  1,  3,
  206,  90,  1,  9,
  226,  26, 10,  6,
  255,   0,  0,  0};

CRGBPalette16 currentPalette = vampirelips_gp;
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
