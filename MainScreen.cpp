#include "MainScreen.h"

MainScreen::MainScreen(int btnA, int btnB, int btnC, uint8_t screenWidth, uint8_t screenHeight, int *currentScreen) {
  _btnA = Button(btnA, INPUT_PULLUP, LOW);
  _btnB = Button(btnB, INPUT_PULLUP, LOW);
  _btnC = Button(btnC, INPUT_PULLUP, LOW);
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;
  _currentScreen = currentScreen;
}

void MainScreen::begin(Adafruit_SSD1306 display) {
  _display = display;
  _posX = 0;
  _posY = 0;
  _isRight = true;
  _isUp = true;
}

void MainScreen::loop(bool isActive) {
  if (isActive) {
    _btnChecker();
  }
}

void MainScreen::tick() {
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

  _display.display();
}