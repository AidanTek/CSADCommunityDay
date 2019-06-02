#include <FastLED.h>


// ~~~~~ Pick your colours here! ~~~~~

uint8_t set1[3] = {255,0,0}; // RGB colour set 1
uint8_t set2[3] = {0,255,0}; // RGB colour set 2
uint8_t set3[3] = {0,0,255}; // RGB colour set 3
uint16_t rate = 600; // How fast the program runs in BPM (beats per minute)

// ~~~~~ No need to change anything else ~~~~~

#define LEDPIN      A2
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    50

uint16_t brightness = 200;

CRGBArray <NUM_LEDS> leds;

uint32_t timerMS = millis();
uint16_t bpm = 60000/rate;
int16_t pos1, pos2, pos3;
uint8_t dir1, dir2, dir3;

void setup() {
  SerialUSB.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, LEDPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
}

void loop() {
  if((millis() - timerMS) > bpm) {
    timerMS = millis();
    if(pos1 <= -1 || pos1 >= 50) {
      uint8_t dice = random(6);
      
      if(dice == 0) {
        dir1 = random(2);
        if(dir1) {
          pos1 = 0;
        }
        else {
          pos1 = 49;
        }
      }
    }
    else {
      if(dir1) {
        leds[pos1] = CRGB(set1[0], set1[1], set1[2]);
        pos1++;
      }
      else {
        leds[pos1] = CRGB(set1[0], set1[1], set1[2]);
        pos1--;
      }
    }

    if(pos2 <= -1 || pos2 >= 50) {
      uint8_t dice = random(6);
      
      if(dice == 0) {
        dir2 = random(2);
        if(dir2) {
          pos2 = 0;
        }
        else {
          pos2 = 49;
        }
      }
    }
    else {
      if(dir2) {
        leds[pos2] = CRGB(set2[0], set2[1], set2[2]);
        pos2++;
      }
      else {
        leds[pos2] = CRGB(set2[0], set2[1], set2[2]);
        pos2--;
      }
    }

    if(pos3 <= -1 || pos3 >= 50) {
      uint8_t dice = random(6);
      
      if(dice == 0) {
        dir3 = random(2);
        if(dir3) {
          pos3 = 0;
        }
        else {
          pos3 = 49;
        }
      }
    }
    else {
      if(dir3) {
        leds[pos3] = CRGB(set3[0], set3[1], set3[2]);
        pos3++;
      }
      else {
        leds[pos3] = CRGB(set3[0], set3[1], set3[2]);
        pos3--;
      }
    }
    
  }

  leds.fadeToBlackBy(20);
  FastLED.show(); 
  FastLED.delay(33);

}
