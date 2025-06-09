#include "Button.h"

Button::Button() {}

Button::Button(uint8_t pin, uint8_t mode, uint8_t activeStatus) {
  _pin = pin;
  _mode = mode;
  _activeStatus = activeStatus;
  _timestamp = 0;

  pinMode(pin, mode);
}

void Button::loop() {
  if (isActive() && _timestamp == 0) {
    _timestamp = millis();
  }
  if (!isActive()) {
    _timestamp = 0;
  }
}

bool Button::isActive() {
  return digitalRead(_pin) == _activeStatus;
}

unsigned long Button::activeTime() {
  return millis() - _timestamp;
}