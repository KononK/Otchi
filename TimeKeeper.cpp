#include "TimeKeeper.h"

TimeKeeper::TimeKeeper(int btnA, int btnB, int btnC) {
  _btnA = Button(btnA, INPUT_PULLUP, LOW);
  _btnB = Button(btnB, INPUT_PULLUP, LOW);
  _btnC = Button(btnC, INPUT_PULLUP, LOW);
}

void TimeKeeper::begin(Adafruit_SSD1306 display, int hour, int minute) {
  begin(display, hour, minute, 0, 0);
}

void TimeKeeper::begin(Adafruit_SSD1306 display, int hour, int minute, int dailyErrorFast, int dailyErrorBehind) {
  _display = display;
  _startingHour = hour;
  _time = { 0, hour, minute, 0 };
  _dailyErrorFast = dailyErrorFast;
  _dailyErrorBehind = dailyErrorBehind;
}

void TimeKeeper::loop() {
  _btnA.loop();
  _btnB.loop();
  _btnC.loop();
  _btnChecker();
  _calculateTime();
}

void TimeKeeper::_btnChecker() {
  if (_btnA.isActive()) {
    if (_flagOnSetup) {
      _flagSetupHour = !_flagSetupHour;
    }
  }

  if (_btnB.isActive()) {
    if (!_flagOnSetup) {
      if (_btnB.activeTime() > 3000) {
        _flagOnSetup = true;
        _flagSetupHour = true;
        _setupTime = _time;
      }
    } else {
      if (_flagSetupHour) {
        _setupTime.Hours += 1;
        if (_setupTime.Hours == 24) {
          _setupTime.Hours = 0;
        }
      } else {
        _setupTime.Minutes += 1;
        if (_setupTime.Minutes == 60) {
          _setupTime.Minutes = 0;
        }
      }
    }
  }

  if (_btnC.isActive()) {
    _flagOnSetup = false;
  }
}

void TimeKeeper::_calculateTime() {
  _timeNow = millis();

  _time.Milis = _timeNow - _timeLast;

  if (_time.Milis >= 1000) {
    _timeLast = _timeNow;
    _time.Seconds += 1;
  }
  if (_time.Seconds == 60) {
    _time.Seconds = 0;
    _time.Minutes += 1;
  }
  if (_time.Minutes == 60) {
    _time.Minutes = 0;
    _time.Hours += 1;
  }
  if (_time.Hours == 24) {
    _time.Hours = 0;
    _time.Days += 1;
  }
  if (_time.Hours == 24 - _startingHour && _correctedToday == 0) {
    delay(_dailyErrorFast * 1000);
    _time.Seconds += _dailyErrorBehind;
    _correctedToday = 1;
  }
  if (_time.Hours == 24 - _startingHour + 2) {
    _correctedToday = 0;
  }
}

Time TimeKeeper::getTime() {
  return _time;
}

void TimeKeeper::showTime() {
  _display.clearDisplay();
  char timeString[9];

  if (!_flagOnSetup) {
    if (_time.Milis < 500) {
      sprintf(timeString, "%02i:%02i:%02i", _time.Hours, _time.Minutes, _time.Seconds);
    } else {
      sprintf(timeString, "%02i %02i %02i", _time.Hours, _time.Minutes, _time.Seconds);
    }
  } else {
    if (_flagSetupHour) {
      if (_time.Milis < 500) {
        sprintf(timeString, "%02i:%02i", _setupTime.Hours, _setupTime.Minutes);
      } else {
        sprintf(timeString, "  :%02i", _setupTime.Minutes);
      }
    } else {
      if (_time.Milis < 500) {
        sprintf(timeString, "%02i:%02i", _setupTime.Hours, _setupTime.Minutes);
      } else {
        sprintf(timeString, "%02i:", _setupTime.Hours);
      }
    }
  }

  _display.setTextSize(2);
  _display.setTextColor(WHITE);
  _display.setCursor(17, 5);
  _display.print(timeString);

  if (!_flagOnSetup) {
    int startPosX = 6;
    int startPosY = 30;
    int nextPos = 24;
    int lastSecond = _time.Seconds % 10;
    if (lastSecond < 5) {
      for (int i = 0; i < lastSecond; i++) {
        _drawImage(startPosX, startPosY, true);
        startPosX += nextPos;
      }
      for (int i = 0; i < 5 - lastSecond; i++) {
        _drawImage(startPosX, startPosY, false);
        startPosX += nextPos;
      }
    } else {
      for (int i = 0; i < lastSecond - 5; i++) {
        _drawImage(startPosX, startPosY, false);
        startPosX += nextPos;
      }
      for (int i = 0; i < 10 - lastSecond; i++) {
        _drawImage(startPosX, startPosY, true);
        startPosX += nextPos;
      }
    }
  }

  _display.display();
}

void TimeKeeper::_drawImage(int x, int y, bool fill) {
  if (fill) {
    _display.fillTriangle(x, y, x + 10, y, x + 10, y + 10, WHITE);
    _display.fillTriangle(x + 20, y + 10, x + 10, y, x + 10, y + 10, WHITE);
    _display.fillTriangle(x + 20, y + 10, x + 10, y + 20, x + 10, y + 10, WHITE);
    _display.fillTriangle(x, y + 20, x + 10, y + 20, x + 10, y + 10, WHITE);
  } else {
    _display.drawTriangle(x, y, x + 10, y, x + 10, y + 10, WHITE);
    _display.drawTriangle(x + 20, y + 10, x + 10, y, x + 10, y + 10, WHITE);
    _display.drawTriangle(x + 20, y + 10, x + 10, y + 20, x + 10, y + 10, WHITE);
    _display.drawTriangle(x, y + 20, x + 10, y + 20, x + 10, y + 10, WHITE);
  }
}