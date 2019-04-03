/*
 * @author Collin Hague
 * screen class for different lcd screens
 */
#include "Screen.h"

class SelectionScreen : public Screen {
  private:
    int state = 0;
  public:
    void left() {
      switch ( state ) {
        case 0:
          state = 1;
          // move cursor to the heat selection
          break;
        case 1:
          state = 2;
          // move cursor to the off selection
          break;
        case 2:
          // do nothing invalid input
          break;
      }
    }
    void right() {
      switch ( state ) {
        case 0:
          // do nothing invalid input
          break;
        case 1:
          state = 0;
          // move cursor to the cp selection
          break;
        case 2:
          state = 1;
          //moves cursor to the heat selection
          break;
      }
    }
    void up() {
      //doesnt do anything
    }
    void down() {
      //doesn't do anything
    }
    int select() {
      switch ( state ) {
        case 0:
          return 1;
        case 1:
          return 3;
        case 2:
          reutrn 5;
      }
    }
    void setup( Adafruit_RGBLCDShield sheild ) {
      //do nothing
    }
    void loop() {
      switch ( state ) {
        case 0:
          
      }
    }
}

