#include <FastLED.h>

// ~~~~~ Pick your colours here! ~~~~~

uint8_t set1[3] = {255,0,0};
uint8_t set2[3] = {0,255,0};
uint8_t set3[3] = {0,0,255};
uint8_t loudness = 20;

// ~~~~~ No need to change anything else ~~~~~

#define LEDPIN      A2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    50

uint16_t brightness = 200;

CRGB leds[NUM_LEDS];

uint8_t soundPin = A5;
uint16_t soundVal;
uint16_t l_soundVal;

uint8_t selector;
uint8_t fade;


void setup() {
  SerialUSB.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, LEDPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
}

void loop() {
  static uint16_t tracker;

  soundVal = analogRead(soundPin);
  if(brightness == 0 && soundVal > (l_soundVal + loudness) || soundVal < (l_soundVal - loudness)) {
    if(l_soundVal > soundVal) {
      fade = (l_soundVal-soundVal)/2;
    }
    else {
      fade = (soundVal-l_soundVal)/2;
    }
    SerialUSB.println(fade);
    
    l_soundVal = soundVal;
    brightness = 200;
    selector = random(3);
    if(selector == 0) {
      for(uint8_t n = 0; n < NUM_LEDS; n++) {
        leds[n] = CRGB(set1[0], set1[1], set1[2]);
      }
      FastLED.show(); 
    }
    else if(selector == 1) {
      for(uint8_t n = 0; n < NUM_LEDS; n++) {
        leds[n] = CRGB(set2[0], set2[1], set2[2]);
      }
      FastLED.show(); 
    }
    else if(selector == 2) {
      for(uint8_t n = 0; n < NUM_LEDS; n++) {
        leds[n] = CRGB(set3[0], set3[1], set3[2]);
      }
      FastLED.show(); 
    }
  }

  if(brightness > 0) {
    brightness--;
    FastLED.setBrightness(brightness);
    FastLED.show(); 
    delay(fade);
    l_soundVal = soundVal;
  }

}
