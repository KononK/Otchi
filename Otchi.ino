#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TimeKeeper.h"
#include "MainScreen.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define BTN_A 10
#define BTN_B 7
#define BTN_C 4

int currentScreen = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TimeKeeper timeKeeper(BTN_A, BTN_B, BTN_C, &currentScreen);
MainScreen mainScreen(BTN_A, BTN_B, BTN_C, SCREEN_WIDTH, SCREEN_HEIGHT, &currentScreen);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  timeKeeper.begin(display, 15, 0);
  timeKeeper.tick(tick);
  mainScreen.begin(display);
}

void loop() {
  timeKeeper.loop(currentScreen == DISPLAY_SCREEN_TIME);
  mainScreen.loop(currentScreen == DISPLAY_SCREEN_MAIN);
  updateScreen();
}

void tick() {
  mainScreen.tick();
}

void updateScreen() {
  switch (currentScreen) {
    case DISPLAY_SCREEN_MAIN:
      mainScreen.display();
      break;
    case DISPLAY_SCREEN_TIME:
      timeKeeper.showTime();
      break;
  }
}