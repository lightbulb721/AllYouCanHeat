#ifndef LCD_H
#define LCD_H
#include "Screen.h"
#include "ExperimentManager.h"
#include <Adafruit_RGBLCDShield.h>
namespace heat {
  class LCD {
    private:
      Screen *screens;
      int screenslength;
      int currentScreen = 0;
      Adafruit_RGBLCDShield sheild;
      Manager manager;
    public:
      void up();
      void down();
      void left();
      void right();
      void select();
      void displayInfo( double *list, int len, int state );
      void loop();
      void setup();
      LCD( Screen* screens, int screenslength, int heatPadPin, int dout, int clk, double calibrationFactor, int motorPin, int thermistorPin0, int thermistorPin1, double kp, double kd, double ki  );
  };
}
#endif
