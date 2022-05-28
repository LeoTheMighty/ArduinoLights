#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( tropical_sun_gp ) {
    0, 213, 65, 42,
   20, 247, 36, 11,
   33, 247, 38, 11,
   45, 213, 65, 42,
   58, 247, 34, 10,
   71, 242, 66, 37,
   81, 247, 36, 11,
   96, 247, 58, 14,
  112, 247, 49, 14,
  119, 239,112, 16,
  130, 247, 79, 19,
  147, 237,117, 17,
  160, 239,111, 16,
  168, 239,161, 21,
  175, 237,122, 16,
  193, 239,117, 16,
  206, 239,161, 21,
  221, 234,161, 19,
  234, 220,141, 43,
  244, 220,151, 68,
  255, 220,151, 68};

CRGBPalette16 currentPalette = tropical_sun_gp;
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
