#ifndef TimeKeeper_h
#define TimeKeeper_h

#include <Adafruit_SSD1306.h>

struct Time {
  int Days;
  int Hours;
  int Minutes;
  int Seconds;
  int Milis;
};

class TimeKeeper {
public:
  TimeKeeper(int btnA, int btnB, int btnC);
  void begin(Adafruit_SSD1306 display, int hour, int minute);
  void begin(Adafruit_SSD1306 display, int hour, int minute, int dailyErrorFast, int dailyErrorBehind);
  void loop();
  Time getTime();
  void showTime();

private:
  Adafruit_SSD1306 _display;
  int _btnA;
  int _btnB;
  int _btnC;
  unsigned long _timeNow = 0;
  unsigned long _timeLast = 0;
  int _startingHour;
  Time _time;
  Time _setupTime;
  int _dailyErrorFast;
  int _dailyErrorBehind;
  int _correctedToday = 1;
  void _calculateTime();
  void _btnChecker();
  void _drawImage(int x, int y, bool fill);
  bool _flagBtnALOW = false;
  bool _flagOnSetup = false;
  bool _flagSetupHour = true;
  unsigned long _btnBHighTimestamp = 0;
};

#endif