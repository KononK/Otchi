#ifndef MainScreen_h
#define MainScreen_h

#include <Adafruit_SSD1306.h>
#include "Assets.h"
#include "Button.h"

#define DISPLAY_SCREEN_MAIN 0
#define DISPLAY_SCREEN_TIME 1

class MainScreen {
public:
  MainScreen(int btnA, int btnB, int btnC, uint8_t screenWidth, uint8_t screenHeight, int *currentScreen);
  void begin(Adafruit_SSD1306 display);
  void loop(bool isActive);
  void tick();
  void display();
private:
  Adafruit_SSD1306 _display;
  Button _btnA;
  Button _btnB;
  Button _btnC;
  uint8_t _screenWidth;
  uint8_t _screenHeight;
  int *_currentScreen;
  void _btnChecker();
  int _posX;
  int _posY;
  bool _isRight;
  bool _isUp;
  uint8_t _animateCode;
};

#endif