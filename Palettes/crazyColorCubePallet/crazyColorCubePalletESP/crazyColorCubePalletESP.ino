#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

DEFINE_GRADIENT_PALETTE( colorcube_gp ) {
    0,  14, 22,  0,
    4,  14,104,  0,
    8,  14,255,  0,
   12,  88, 22,  0,
   16,  88,104,  0,
   20,  88,255,  0,
   24, 255, 22,  0,
   28, 255,104,  0,
   32, 255,255,  0,
   36,   0, 22, 44,
   40,   0,104, 44,
   44,   0,255, 44,
   48,  14,  0, 44,
   52,  14, 22, 44,
   56,  14,104, 44,
   60,  14,255, 44,
   64,  88,  0, 44,
   68,  88, 22, 44,
   72,  88,104, 44,
   76,  88,255, 44,
   80, 255,  0, 44,
   84, 255, 22, 44,
   89, 255,104, 44,
   93, 255,255, 44,
   97,   0, 22,255,
  101,   0,104,255,
  105,   0,255,255,
  109,  14,  0,255,
  113,  14, 22,255,
  117,  14,104,255,
  121,  14,255,255,
  125,  88,  0,255,
  129,  88, 22,255,
  133,  88,104,255,
  137,  88,255,255,
  141, 255,  0,255,
  145, 255, 22,255,
  149, 255,104,255,
  153,   2,  0,  0,
  157,  14,  0,  0,
  161,  41,  0,  0,
  165,  88,  0,  0,
  170, 157,  0,  0,
  174, 255,  0,  0,
  178,   0,  4,  0,
  182,   0, 22,  0,
  186,   0, 55,  0,
  190,   0,104,  0,
  194,   0,169,  0,
  198,   0,255,  0,
  202,   0,  0,  2,
  206,   0,  0, 15,
  210,   0,  0, 44,
  214,   0,  0, 92,
  218,   0,  0,160,
  222,   0,  0,255,
  226,   0,  0,  0,
  230,   1,  3,  1,
  234,   9, 15, 10,
  238,  27, 39, 30,
  242,  58, 73, 62,
  246, 106,121,109,
  250, 169,180,172,
  255, 255,255,255};


CRGBPalette16 currentPalette = colorcube_gp;
#define currentBlending LINEARBLEND

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(4.5, 500);
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
