/*
 * @author Collin Hague
 * screen class for different lcd screens
 * note: need to update print.h and print.cpp to github file basic install doesn't include printf in the print.h file
 */
#include "Screen.h"

using namespace heat;
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
    void setup( Adafruit_RGBLCDShield &shield ) {
      //do nothing
    }
    void loop( Adafruit_RGBLCDShield &shield ) {
	  shield.clear();
      shield.print("CP    HEAT   OFF");
      switch ( state ) {
        case 0:
          shield.setCursor( 0, 1 );
    		  break;
    		case 1:
    		  shield.setCursor( 8, 1 );
    		  break;
    		case 2:
    		  shield.setCursor( 15, 1 );
    		  break;
      }
      shield.blink();
    }
};

class DetermineCPScreen : public Screen {
  public:
    void loop( Adafruit_RGBLCDShield &shield ) {
      shield.clear();
      shield.print("Determining CP");
      shield.setCursor( 0, 1 );
      shield.print("Select to Cancel");
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
    void loop( Adafruit_RGBLCDShield &shield ) {
      shield.clear();
      shield.printf("CP : %.2f", this->finalTemp );
      shield.setCursor( 0, 1 );
      shield.print( "KJ / KG * K" );
      shield.noBlink();
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

class SetTemperatureScreen : public Screen {
  private:
    int temperature = 25;
    int state = 0;
  public:
    void up() {
      switch ( state ) {
        case 0:
          if ( temperature <= 30 ) {
            temperature += 10;
          } else {
            temperature = temperature % 10;
          }
          break;
        case 1:
          if ( temperature % 10 < 9 ) {
            temperature += 1;
          } else {
            temperature -= 9;
          }
      }
    }
    void down() {
      switch ( state ) {
        case 0:
          if ( temperature > 10 ) {
            temperature -= 10;
          } else {
            temperature = 30 + temperature % 10;
          }
          break;
        case 1:
          if ( temperature % 10 > 0 ) {
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
    void loop( Adafruit_RGBLCDShield &shield ) {
      shield.clear();
      shield.print( "Set Temperature" );
      shield.setCursor( 0, 1 );
      shield.printf( "%2d", this->temperature );
      switch ( state ) {
        case 0:
          shield.setCursor( 0, 1 );
          break;
        case 1:
          shield.setCursor( 1, 1 );
          break;
      }
      shield.blink();
    }
};

class ReportTemperatureScreen : public Screen {
  private:
    double currentTemp;
    double finalTemp;
  public:
    int select() {
      return 0;
    }
    void loop( Adafruit_RGBLCDShield &shield ) {
      shield.clear();
      shield.printf( "Current: %.2f", this->currentTemp );
      shield.setCursor( 0, 1 );
      shield.printf( "Final: %.2f", this->finalTemp );
      shield.noBlink();
    }
    void displayInfo( double *list, int len ) {
      if ( len > 1 ) {
        currentTemp = list[0];
        finalTemp = list[1];
      }
    }
};
