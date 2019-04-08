#ifndef SCREEN_H
#define SCREEN_H
#include <Adafruit_RGBLCDShield.h>
namespace heat {

class Screen {
  public:
  void up(){return;};
  void down(){return;};
  void left(){return;};
  void right(){return;};
  int select(){return -1;};
  void displayInfo( double *list, int len ){return;};
  void setup( Adafruit_RGBLCDShield sheild ){return;};
  void loop( Adafruit_RGBLCDShield sheild ){return;};
 };
 class SelectionScreen : public Screen {};
 class DetermineCPScreen : public Screen {};
 class ShowCPScreen : public Screen {};
 class SetTemperatureScreen : public Screen {};
 class ReportTemperatureScreen : public Screen {};
}
#endif
