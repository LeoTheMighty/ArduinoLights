#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( patriot_black_gp ) {
    0, 227,  1,  1,
   61, 255,255,255,
  127,   0,  0,125,
  191,   0,  0,  0,
  252, 227,  1,  1,
  255, 227,  1,  1};

CRGBPalette16 currentPalette = patriot_black_gp;
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
