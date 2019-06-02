#include <FastLED.h>

// ~~~~~ Pick your colours here! ~~~~~

uint8_t set1[3] = {255,0,0}; // RGB colour set 1
uint8_t set2[3] = {0,255,0}; // RGB colour set 2
uint8_t set3[3] = {0,0,255}; // RGB colour set 3
uint16_t rate = 120; // How fast the program runs in BPM (beats per minute)

// ~~~~~ No need to change anything else ~~~~~

#define LEDPIN      A2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    50

uint16_t brightness = 200;

CRGB leds[NUM_LEDS];

uint8_t phase;
uint16_t bpm = 60000/rate;

void setup() {
  SerialUSB.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, LEDPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);

}

void loop() {
  for(uint8_t n = 0; n < NUM_LEDS; n++) {
    if((n + phase) % 3 == 0) {
      leds[n] = CRGB(set1[0], set1[1], set1[2]);
    }
    else if(((n + phase) + 1) % 3 == 0) {
      leds[n] = CRGB(set2[0], set2[1], set2[2]);
    }
    else if(((n + phase) + 2) % 3 == 0) {
      leds[n] = CRGB(set3[0], set3[1], set3[2]);
    }
  }
  FastLED.show(); 
  
  phase++;
  delay(bpm);
  
}
