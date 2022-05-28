#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( GPS_Nature_Browns_gp ) {
    0, 220,186,  4,
    4, 182,164,  2,
    8, 148,146,  1,
   20, 100, 79,  2,
   33,  63, 33,  6,
   42, 106, 47,  5,
   51, 163, 62,  5,
   57,  79, 47,  1,
   63,  29, 33,  1,
   72,  45, 32,  1,
   80,  65, 31,  1,
   84,  64, 29,  2,
   88,  63, 26,  4,
   95,  77, 35,  7,
  101,  92, 45, 11,
  108,  95, 63,  2,
  114, 100, 85,  1,
  123,  98, 49,  1,
  131,  97, 23,  1,
  135,  82, 11,  1,
  140,  69,  4,  1,
  146,  46, 15,  1,
  149,  27, 34,  1,
  153,  20, 15,  1,
  160,  14,  4,  1,
  167,  10, 10,  1,
  173,   7, 18,  1,
  180,  29,  9,  1,
  185,  69,  4,  1,
  189,  36,  7,  1,
  200,  15, 10,  1,
  206,  13,  4,  1,
  213,  12,  1,  1,
  223,  24,  2,  1,
  232,  42,  4,  1,
  243,   7,  1,  1,
  255,   0,  1,  0};

CRGBPalette16 currentPalette = GPS_Nature_Browns_gp;
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
