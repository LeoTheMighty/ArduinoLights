# 1 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletUno/desertPalletUno.ino"
# 2 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletUno/desertPalletUno.ino" 2






CRGB leds[240];



 extern const TProgmemRGBGradientPalette_byte bhw1_07_gp[] 
# 12 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletUno/desertPalletUno.ino" 3
__attribute__((__progmem__)) 
# 12 "/Users/leonid.belyi/personal/ArduinoLights/Palettes/desertPallet/desertPalletUno/desertPalletUno.ino"
= {
    0, 232, 65, 1,
  255, 229,227, 1};

CRGBPalette16 currentPalette = bhw1_07_gp;


void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<WS2812B, 3, GRB>(leds, 240).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(64);
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

    for( int i = 0; i < 240; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
}
