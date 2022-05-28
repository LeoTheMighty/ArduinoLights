#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( emerald_city_gp ) {
    0,   6, 74, 18,
   12,  10,166, 38,
   17,  97,233, 30,
   25,  17,237, 55,
   33,  10,166, 38,
   38,  97,233, 30,
   48,  59,239, 18,
   53,   6, 74, 18,
   63,  10,166, 38,
   71,   8, 30,  5,
   81,  97,233, 30,
   91,  12,180,  1,
   99,  97,233, 30,
  109,  12,180,  1,
  119,  10,166, 38,
  127,  17,237, 55,
  132,   8, 51, 16,
  140,  10,166, 38,
  145,   6, 74, 18,
  158,  59,239, 18,
  168,   1,221, 21,
  173,  10,166, 38,
  181,  15,104, 32,
  191,   6, 74, 18,
  201,  15,104, 32,
  211,  59,239, 18,
  219,   8, 51, 16,
  224,   1,135,  1,
  229,  10,166, 38,
  239,  59,239, 18,
  247,  10,166, 38,
  255,   6, 74, 18};

CRGBPalette16 currentPalette = emerald_city_gp;
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
