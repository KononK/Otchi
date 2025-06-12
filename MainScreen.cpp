#include "MainScreen.h"

MainScreen::MainScreen(int btnA, int btnB, int btnC, uint8_t screenWidth, uint8_t screenHeight, int *currentScreen) {
  _btnA = Button(btnA, INPUT_PULLUP, LOW);
  _btnB = Button(btnB, INPUT_PULLUP, LOW);
  _btnC = Button(btnC, INPUT_PULLUP, LOW);
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;
  _currentScreen = currentScreen;
  _animateCode = 0;
}

void MainScreen::begin(Adafruit_SSD1306 display) {
  _display = display;
  _posX = 32;
  _posY = 30;
  _isRight = true;
  _isUp = true;
}

void MainScreen::loop(bool isActive) {
  if (isActive) {
    _btnChecker();
  }
}

void MainScreen::tick() {
  _animateCode++;
  if (_animateCode == 5) {
    _animateCode = 0;
  }

  if (_isRight) {
    _posX++;
    if (_posX == _screenWidth - 1) {
      _isRight = false;
    }
  } else {
    _posX--;
    if (_posX == 0) {
      _isRight = true;
    }
  }

  if (_isUp) {
    _posY += 10;
    _isUp = false;
  } else {
    _posY -= 10;
    _isUp = true;
  }
}

void MainScreen::_btnChecker() {
  _btnA.loop();
  _btnB.loop();
  _btnC.loop();

  if (_btnA.isActive()) {
  }

  if (_btnB.isActive()) {
    *_currentScreen = DISPLAY_SCREEN_TIME;
  }

  if (_btnC.isActive()) {
  }
}

void MainScreen::display() {
  _display.clearDisplay();

  _display.drawPixel(_posX, _posY, WHITE);

  uint8_t eggSize = 16;
  uint8_t x = (_display.width()  - eggSize) / 2;
  uint8_t y = 28;

  switch(_animateCode) {
    case 0:
      _display.drawBitmap(x, y, ASSETS_EGG_1, eggSize, eggSize, WHITE);
      break;
    case 1:
      _display.drawBitmap(x, y + 1, ASSETS_EGG_2, eggSize, eggSize, WHITE);
      break;
    case 2:
      _display.drawBitmap(x, y - 3, ASSETS_EGG_3, eggSize, eggSize, WHITE);
      break;
    case 3:
      _display.drawBitmap(x, y - 5, ASSETS_EGG_4, eggSize, eggSize, WHITE);
      break;
    case 4:
      _display.drawBitmap(x, y - 4, ASSETS_EGG_3, eggSize, eggSize, WHITE);
      break;
  }

  _display.drawLine(0, 44, 127, 44, WHITE);

  _display.display();
}