#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( partytime_gp ) {
    0, 249, 21, 44,
   12, 237,  7, 69,
   33,  20, 33, 60,
   66, 237, 12, 11,
   84,   1, 79,122,
  101, 249, 47, 29,
  124,  45,  1,128,
  145, 244,  7,120,
  165,   1, 79,122,
  191, 249,  7, 52,
  211, 194, 85, 24,
  221,   1, 79,122,
  239, 237, 12, 11,
  255, 234, 12, 21};

CRGBPalette16 currentPalette = partytime_gp;
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
