#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TimeKeeper.h"

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

#define BTN_A 2
#define BTN_B 3
#define BTN_C 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TimeKeeper timeKeeper(BTN_A, BTN_B, BTN_C);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  timeKeeper.begin(display, 15, 0);
}

void loop() {
  timeKeeper.loop();
  updateScreen();
}

void updateScreen() {
  timeKeeper.showTime();
}