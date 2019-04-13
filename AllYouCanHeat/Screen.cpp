/*
 * @author Collin Hague
 * screen class for different lcd screens
 * note: need to update print.h and print.cpp to github file basic install doesn't include printf in the print.h file
 */
#include "Screen.h"

using namespace heat;
void SelectionScreen::right() {
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
void SelectionScreen::left() {
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
void SelectionScreen::up() {
  //doesnt do anything
}
void SelectionScreen::down() {
  //doesn't do anything
}
int SelectionScreen::select() {
  switch ( state ) {
    case 0:
      return 1;
    case 1:
      return 3;
    case 2:
      return 0;
  }
  return 0;
}
void SelectionScreen::setup( Adafruit_RGBLCDShield &shield ) {
  //do nothing
}
void SelectionScreen::loop( Adafruit_RGBLCDShield &shield ) {
 #ifdef DEBUG
 Serial.println("Displaying Selection Screen");
 #endif
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
  shield.cursor();
  shield.noBlink();
}
void SelectionScreen::displayInfo( double *list, int len ){
  return;
}

void DetermineCPScreen::up() {return;}
void DetermineCPScreen::down() {return;}
void DetermineCPScreen::left() {return;}
void DetermineCPScreen::right() {return;}
void DetermineCPScreen::setup( Adafruit_RGBLCDShield &shield ) {return;}
void DetermineCPScreen::displayInfo( double *list, int len ){return;}
void DetermineCPScreen::loop( Adafruit_RGBLCDShield &shield ) {
  shield.print("Determining CP");
  shield.setCursor( 0, 1 );
  shield.print("Select to Cancel");
  shield.noBlink();
}
int DetermineCPScreen::select() {
  return 0;
}

void ShowCPScreen::up() {return;}
void ShowCPScreen::down() {return;}
void ShowCPScreen::left() {return;}
void ShowCPScreen::right() {return;}
void ShowCPScreen::setup( Adafruit_RGBLCDShield &shield ) {return;}
void ShowCPScreen::loop( Adafruit_RGBLCDShield &shield ) {
  shield.printf("CP : %d", int(this->finalTemp) );
  shield.setCursor( 0, 1 );
  shield.print( "KJ / KG * K" );
  shield.noBlink();
}
void ShowCPScreen::displayInfo( double *list, int len ) {
  if ( len > 0 ) {
    finalTemp = list[0];
  }
}
int ShowCPScreen::select() {
  return 0;
}

void SetTemperatureScreen::up() {
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
void SetTemperatureScreen::down() {
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
void SetTemperatureScreen::left() {
  switch ( state ) {
    case 0:
      // do nothing
      break;
    case 1:
      state = 0;
      break;
  }
}
void SetTemperatureScreen::right() {
  switch ( state ) {
    case 0:
      state = 1;
      break;
    case 1:
      // do nothing
      break;
  }
}
int SetTemperatureScreen::select() {
  return temperature;
}
void SetTemperatureScreen::loop( Adafruit_RGBLCDShield &shield ) {
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
void SetTemperatureScreen::setup( Adafruit_RGBLCDShield &shield ) {return;}
void SetTemperatureScreen::displayInfo( double *list, int len ){return;}

int ReportTemperatureScreen::select() {
  return 0;
}
void ReportTemperatureScreen::up() {return;}
void ReportTemperatureScreen::down() {return;}
void ReportTemperatureScreen::left() {return;}
void ReportTemperatureScreen::right() {return;}
void ReportTemperatureScreen::setup( Adafruit_RGBLCDShield &shield ) {return;}
void ReportTemperatureScreen::loop( Adafruit_RGBLCDShield &shield ) {
  shield.printf( "Current: %d", int(this->currentTemp) );
  shield.setCursor( 0, 1 );
  shield.printf( "Final: %d", int(this->finalTemp) );
  shield.noBlink();
}
void ReportTemperatureScreen::displayInfo( double *list, int len ) {
  if ( len > 1 ) {
    currentTemp = list[1];
    finalTemp = list[0];
  }
}
