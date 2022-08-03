//Ethan Rawlins Custom ARGB Led Strip Driver

// FastLed is required for use of neopixel led strip.
#include <FastLED.h>

#define NUM_LEDS 144
#define LED_DATA_PIN 2
#define LED_DATA_PIN_2 4

CRGB firstLeds[NUM_LEDS];
CRGB secondLeds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE (blue_purple) {
  0, 0, 66, 255, // blue
  255, 255, 0, 255 // purple
};
CRGBPalette16 bluePurplePal = blue_purple;

DEFINE_GRADIENT_PALETTE (blue_green) {
  0, 0, 66, 255, // blue
  255, 0, 255, 0 // green
};
CRGBPalette16 blueGreenPal = blue_green;

DEFINE_GRADIENT_PALETTE (white) {
  0, 255, 255, 200, // white
  255, 255, 255, 200 // white
};
CRGBPalette16 whitePal = white;

int firstGradientIndex = 0; // Index for starting gradient color
int secondGradientIndex = 123; // Index for second string of leds
#define GRADIENT_MOVE_SPEED 80 // speed (milliseconds) for how fast the color gradient moves

void setup() {
// initialize serial communication
  Serial.begin(9600);
 
// configure fastLED
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(firstLeds, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_DATA_PIN_2, GRB>(secondLeds, NUM_LEDS);
  FastLED.setBrightness(100);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  fillColor(bluePurplePal);
  FastLED.show();
}

void fillColor(CRGBPalette16 colorPal) {
// moving gradient color fill
    fill_palette(firstLeds, NUM_LEDS, firstGradientIndex, 255 / NUM_LEDS, colorPal, 255, LINEARBLEND);
    fill_palette(secondLeds, NUM_LEDS, secondGradientIndex, 255 / NUM_LEDS, colorPal, 255, LINEARBLEND);
    EVERY_N_MILLISECONDS(GRADIENT_MOVE_SPEED) {
      firstGradientIndex++;
      secondGradientIndex++;
    }
  FastLED.show();  
}
