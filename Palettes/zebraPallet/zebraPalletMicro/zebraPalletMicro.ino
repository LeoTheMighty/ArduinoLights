#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( zebra_gp ) {
    0,   0,  0,  0,
   12,   0,  0,  0,
   19, 255,255,255,
   31, 255,255,255,
   63,   0,  0,  0,
   89,   0,  0,  0,
  114, 255,255,255,
  140, 255,255,255,
  165,   0,  0,  0,
  191,   0,  0,  0,
  223, 255,255,255,
  235, 255,255,255,
  242,   0,  0,  0,
  255,   0,  0,  0};

CRGBPalette16 currentPalette = zebra_gp;
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
