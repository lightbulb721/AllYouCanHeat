#ifndef SCREEN_H
#define SCREEN_H
#include <Adafruit_RGBLCDShield.h>
namespace heat {

 class Screen {
  public:
  void up();
  void down();
  void left();
  void right();
  int select();
  void setup( Adafruit_RGBLCDShield sheild );
  void loop( Adafruit_RGBLCDShield sheild );
 };
}
#endif
