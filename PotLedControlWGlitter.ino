#include <FastLED.h>

#define LED_PIN     6
#define pot_pin  2
float potVal = 0;

// Information about the LED strip itself
#define NUM_LEDS    30
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGBPalette256 colorPalette = RainbowColors_p;

#define BRIGHTNESS  10



#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky

// How many seconds to show each temperature before switching
#define DISPLAYTIME 20
// How many seconds to show black between switches
#define BLACKTIME   3
String potStr = "pot=";

void loop()
{
  potVal = analogRead(pot_pin);
  String printStr = potStr + potVal;
  Serial.println(printStr);
  uint8_t color = (potVal / 1023.0) * 255;
  Serial.println(color);
  
  // draw a generic, no-name rainbow
  static uint8_t starthue = 0;
  CRGB currentColor = ColorFromPalette( colorPalette, color, 100, LINEARBLEND);
  fill_solid( leds, NUM_LEDS, currentColor);
  addGlitter(50);
  
  FastLED.show();
  FastLED.delay(55);
}

void setup() {
  delay( 3000 ); // power-up safety delay
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  analogReference(INTERNAL);
 Serial.begin(9600);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    //leds[ random16(NUM_LEDS) ] += CRGB::White;
    leds[ random16(NUM_LEDS) ] += CRGB::White;
    leds[ random16(NUM_LEDS) ].maximizeBrightness();
  }
}
