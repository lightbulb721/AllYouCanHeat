#ifndef SCREEN_H
#define SCREEN_H
#include <Adafruit_RGBLCDShield.h>
#include "Arduino.h"
namespace heat {

class Screen {
  public:
  virtual void up() =0;
  virtual void down() =0;
  virtual void left() =0;
  virtual void right() =0;
  virtual int select() =0;
  virtual void displayInfo( double *list, int len ) =0;
  virtual void setup( Adafruit_RGBLCDShield &sheild ) =0;
  virtual void loop( Adafruit_RGBLCDShield &sheild ) =0;
 };
 class SelectionScreen : public Screen {
  private:
    int state = 0;
  public:
  void up() override;
  void down() override;
  void left() override;
  void right() override;
  int select() override;
  void displayInfo( double *list, int len ) override;
  void setup( Adafruit_RGBLCDShield &sheild ) override;
  void loop( Adafruit_RGBLCDShield &sheild ) override;
};
 class DetermineCPScreen : public Screen {
  void up() override;
  void down() override;
  void left() override;
  void right() override;
  int select() override;
  void displayInfo( double *list, int len ) override;
  void setup( Adafruit_RGBLCDShield &sheild ) override;
  void loop( Adafruit_RGBLCDShield &sheild ) override;
};
 class ShowCPScreen : public Screen {
  private:
  double finalTemp = 0;
  public:
  void up() override;
  void down() override;
  void left() override;
  void right() override;
  int select() override;
  void displayInfo( double *list, int len ) override;
  void setup( Adafruit_RGBLCDShield &sheild ) override;
  void loop( Adafruit_RGBLCDShield &sheild ) override;
};
 class SetTemperatureScreen : public Screen {
  private:
    int temperature = 25;
    int state = 0;
  public:
  void up() override;
  void down() override;
  void left() override;
  void right() override;
  int select() override;
  void displayInfo( double *list, int len ) override;
  void setup( Adafruit_RGBLCDShield &sheild ) override;
  void loop( Adafruit_RGBLCDShield &sheild ) override;
};
 class ReportTemperatureScreen : public Screen {
  private:
    double currentTemp;
    double finalTemp;
  public:
  void up() override;
  void down() override;
  void left() override;
  void right() override;
  int select() override;
  void displayInfo( double *list, int len ) override;
  void setup( Adafruit_RGBLCDShield &sheild ) override;
  void loop( Adafruit_RGBLCDShield &sheild ) override;
};
}
#endif
