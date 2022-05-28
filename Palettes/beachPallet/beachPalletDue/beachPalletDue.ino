#include <FastLED.h>

#define LED_PIN     21
#define NUM_LEDS    480
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE( tropical_beach_gp ) {
    0,   1, 61, 85,
   38,   9,176,255,
   63, 255, 97,  5,
   96, 255, 26, 19,
  130, 206,201,  6,
  165, 255, 29, 16,
  191, 255, 97,  5,
  221,   9,176,255,
  247,   1, 61, 85,
  255,   1, 61, 85};

CRGBPalette16 currentPalette = tropical_beach_gp;
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
