#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
public:
  Button();
  Button(uint8_t pin, uint8_t mode, uint8_t activeStatus);
  void loop();
  bool isActive();
  unsigned long activeTime();

private:
  uint8_t _pin;
  uint8_t _mode;
  uint8_t _activeStatus;
  unsigned long _timestamp;
};

#endif