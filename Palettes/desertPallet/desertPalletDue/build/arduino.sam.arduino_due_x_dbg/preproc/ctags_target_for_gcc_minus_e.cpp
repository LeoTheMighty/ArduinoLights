# 1 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletDue/desertPalletDue.ino"
# 2 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletDue/desertPalletDue.ino" 2






CRGB leds[480];



__attribute__ ((aligned (4))) extern const TProgmemRGBGradientPalette_byte bhw1_07_gp[] = {
    0, 232, 65, 1,
  255, 229,227, 1};

CRGBPalette16 currentPalette = bhw1_07_gp;


void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<WS2812B, 21, GRB>(leds, 480).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(64);
    FastLED.setMaxPowerInVoltsAndMilliamps(4.5, 1000);
}


void loop(){
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors( startIndex);

    FastLED.show();
    FastLED.delay(1000 / 100);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
    uint8_t brightness = 255;

    for( int i = 0; i < 480; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
}
