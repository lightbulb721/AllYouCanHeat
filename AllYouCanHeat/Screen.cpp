/*
 * @author Collin Hague
 * screen class for different lcd screens
 */
#include "Screen.h"

class SelectionScreen : public Screen {
  private:
    int state = 0;
  public:
    void right() {
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
    void left() {
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
          return 5;
      }
    }
    void setup( Adafruit_RGBLCDShield sheild ) {
      //do nothing
    }
    void loop( Adafruit_RGBLCDShield sheild ) {
	  sheild.clear();
      sheild.print("CP    HEAT   OFF");
      switch ( state ) {
        case 0:
          sheild.setCursor( 0, 1 );
    		  break;
    		case 1:
    		  sheild.setCursor( 8, 1 );
    		  break;
    		case 2:
    		  sheild.setCursor( 15, 1 );
    		  break;
      }
      sheild.blink();
    }
};

class DetermineCPScreen : public Screen {
  public:
    void loop( Adafruit_RGBLCDShield sheild ) {
      sheild.clear();
      sheild.print("Determining CP");
      sheild.setCursor( 0, 1 );
      sheild.print("Select to Cancel");
      shield.noBlink();
    }
    int select() {
      return 0;
    }
};

class ShowCPScreen : public Screen {
  private:
    double finalTemp = 0;
  public:
    void loop( Adafruid_RGBLCDSheild sheild ) {
      sheild.clear();
      sheild.printf("CP : %.2f", this->finalTemp );
      sheild.setCursor( 0, 1 );
      sheild.print( "KJ / KG * K" );
      sheild.noBlink();
    }
    void displayInfo( double *list, int len ) {
      if ( len > 0 ) {
        finalTemp = list[0];
      }
    }
    int select() {
      return 0;
    }
};

class setTemperatureScreen : public Screen {
  private:
    int temperature = 25;
    int state = 0;
  public:
    void up() {
      switch ( state ) {
        case 0:
          if temperature <= 30 {
            temperature += 10;
          } else {
            temperature = temperature % 10;
          }
          break;
        case 1:
          if temperature % 10 < 9 {
            temperature += 1;
          } else {
            temperature -= 9;
          }
      }
    }
    void down() {
      switch ( state ) {
        case 0:
          if temperature > 10 {
            temperature -= 10;
          } else {
            temperature = 30 + temperature % 10;
          }
          break;
        case 1:
          if temperature % 10 > 0 {
            temperature -= 1;
          } else {
            temperature += 9;
          }
      }
    }
    void left() {
      switch ( state ) {
        case 0:
          // do nothing
          break;
        case 1:
          state = 0;
          break;
      }
    }
    void right() {
      switch ( state ) {
        case 0:
          state = 1;
          break;
        case 1:
          // do nothing
          break;
      }
    }
    int select() {
      return temperature;
    }
};


