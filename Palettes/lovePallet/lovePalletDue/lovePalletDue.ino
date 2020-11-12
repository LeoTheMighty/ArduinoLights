#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

DEFINE_GRADIENT_PALETTE( violent_pink_red_gp ) {
    0, 252,215,221,
   25, 252,215,221,
   25, 249,146,160,
   51, 249,146,160,
   51, 247, 92,112,
   76, 247, 92,112,
   76, 244, 51, 73,
  102, 244, 51, 73,
  102, 242, 22, 44,
  127, 242, 22, 44,
  127, 224,  8, 25,
  153, 224,  8, 25,
  153, 153,  8, 21,
  178, 153,  8, 21,
  178, 100,  8, 16,
  204, 100,  8, 16,
  204,  58,  8, 12,
  229,  58,  8, 12,
  229,  30,  6,  8,
  255,  30,  6,  8};




CRGBPalette16 currentPalette = violent_pink_red_gp;
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
