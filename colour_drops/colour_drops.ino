#include <FastLED.h>

// ~~~~~ Pick your colours here! ~~~~~

uint8_t set1[3] = {255, 0, 0}; // RGB colour set 1
uint8_t set2[3] = {0, 255, 0}; // RGB colour set 2
uint8_t set3[3] = {0, 0, 255}; // RGB colour set 3
uint16_t rate = 240; // How fast the program runs in BPM (beats per minute)
uint8_t density = 10; // How many LEDs to change each step

// ~~~~~ No need to change anything else ~~~~~

#define LEDPIN      A2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    50

uint16_t brightness = 200;

CRGBArray <NUM_LEDS> leds;

uint32_t timerMS = millis();
uint16_t bpm = 60000 / rate;

void setup() {
  SerialUSB.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, LEDPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
}

void loop() {
  if ((millis() - timerMS) > bpm) {
    timerMS = millis();
    int rc = random(3);

    for (uint8_t n = 0; n < density; n++) {
      int r = random(NUM_LEDS);

      if (rc == 0) {
        leds[r] = CRGB(set1[0], set1[1], set1[2]);
      }
      else if (rc == 1) {
        leds[r] = CRGB(set2[0], set2[1], set2[2]);
      }
      else if (rc == 2) {
        leds[r] = CRGB(set3[0], set3[1], set3[2]);
      }

    }
  }

  leds.fadeToBlackBy(20);
  FastLED.show();
  FastLED.delay(33);
}
