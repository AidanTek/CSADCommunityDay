#include <FastLED.h>

// ~~~~~ Pick your colours here! ~~~~~

uint8_t set1[3] = {255,0,0};
uint8_t set2[3] = {0,255,0};
uint8_t set3[3] = {0,0,255};

// ~~~~~ No need to change anything else ~~~~~

#define LEDPIN      A2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    50

uint16_t brightness = 200;

CRGB leds[NUM_LEDS];

uint8_t potPin = A5;
uint16_t potVal;
uint16_t l_potVal;

uint8_t spd;
uint8_t phase;
uint8_t tracker;

void setup() {
  SerialUSB.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, LEDPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
}

void loop() {
  potVal = analogRead(potPin);
  if(potVal > (l_potVal + 2) || potVal < (l_potVal - 2)) { 
    l_potVal = potVal;
    spd = map(potVal, 0, 1023, 50, 1);
    SerialUSB.println(spd);
  }

  if(tracker == 100) { 
    tracker = 0;
    phase++;
    if(phase == 6) phase = 0;
  }

  if(phase == 0) {
    uint8_t r = (set1[0]/100)*tracker;
    uint8_t g = (set1[1]/100)*tracker;
    uint8_t b = (set1[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(r, g, b);
    }
  }
  else if(phase == 1) {
    uint8_t r = (set1[0]/100)*tracker;
    uint8_t g = (set1[1]/100)*tracker;
    uint8_t b = (set1[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(set1[0]-r, set1[1]-g, set1[2]-b);
    }
  }
  else if(phase == 2) {
    uint8_t r = (set2[0]/100)*tracker;
    uint8_t g = (set2[1]/100)*tracker;
    uint8_t b = (set2[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(r, g, b);
    }
  }
  else if(phase == 3) {
    uint8_t r = (set2[0]/100)*tracker;
    uint8_t g = (set2[1]/100)*tracker;
    uint8_t b = (set2[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(set2[0]-r, set2[1]-g, set2[2]-b);
    }
  }
  else if(phase == 4) {
    uint8_t r = (set3[0]/100)*tracker;
    uint8_t g = (set3[1]/100)*tracker;
    uint8_t b = (set3[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(r, g, b);
    }
  }
  else if(phase == 5) {
    uint8_t r = (set3[0]/100)*tracker;
    uint8_t g = (set3[1]/100)*tracker;
    uint8_t b = (set3[2]/100)*tracker;
    for(uint8_t n = 0; n < NUM_LEDS; n++) {
      leds[n] = CRGB(set3[0]-r, set3[1]-g, set3[2]-b);
    }
  }
  FastLED.show();
  delay(spd);
  tracker++;
}
