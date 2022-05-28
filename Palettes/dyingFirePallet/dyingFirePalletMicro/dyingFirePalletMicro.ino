#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    240 
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( shimmishake_gp ) {
    0, 148,164,  9,
    7, 229,227,  1,
   22,  24, 13,  3,
   33, 229,227,  1,
   43,  24, 13,  3,
   61, 232, 75,  1,
   71,  24, 13,  3,
   89, 232, 75,  1,
  101, 232,  3,  1,
  114, 232, 75,  1,
  122,  24, 13,  3,
  135, 232, 75,  1,
  153, 229,227,  1,
  160, 232,  3,  1,
  173,  24, 13,  3,
  186, 229,227,  1,
  204,  24, 13,  3,
  219, 229,227,  1,
  232, 232,  3,  1,
  239, 232, 40,  1,
  252, 232,  3,  1,
  255, 232,  3,  1};

CRGBPalette16 currentPalette = shimmishake_gp;
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
