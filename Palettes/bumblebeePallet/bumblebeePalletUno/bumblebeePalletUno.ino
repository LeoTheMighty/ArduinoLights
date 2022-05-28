#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( bumblebee_gp ) {
    0, 255,255,  0,
   12, 255,255,  0,
   38,   0,  0,  0,
   63, 255,255,  0,
   89, 255,255,  0,
  114,   0,  0,  0,
  140,   0,  0,  0,
  165, 255,255,  0,
  191, 255,255,  0,
  216,   0,  0,  0,
  242, 255,255,  0,
  255, 255,255,  0};

CRGBPalette16 currentPalette = bumblebee_gp;
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
