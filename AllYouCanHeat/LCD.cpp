/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "LCD.h"
#include "Arduino.h"

#define DEBUG

#define ON 0x7
#define OFF 0x0

using namespace heat;

LCD::LCD( Screen **screens, int screenslength, int heatPadPin, int dout, int clk, double calibrationFactor, int motorPin, uint8_t thermistorPin0, uint8_t thermistorPin1, double kp, double kd, double ki  ) {
  this->screens = screens;
  this->screenslength = screenslength;
  this->sheild = Adafruit_RGBLCDShield();
  this->manager = Manager( heatPadPin, dout, clk, calibrationFactor, motorPin, thermistorPin0, thermistorPin1, kp, kd, ki );  
}

void LCD::setup() {
  this->sheild.begin( 16, 2 );
  this->sheild.print( "All You Can Heat" );
  this->sheild.setBacklight( ON );
  for( int i = 0; i < this->screenslength; i++ ) {
    this->screens[ i ]->setup( this->sheild );
  }
  manager.setup();
}
void LCD::loop() {
  manager.loop();
  uint8_t buttons = this->sheild.readButtons();

  if ( buttons != this->lastButton ) {
    if ( buttons & BUTTON_UP ) {
      this->up();
    } else if ( buttons & BUTTON_DOWN ) {
      this->down();
    } else if ( buttons & BUTTON_RIGHT ) {
      this->right();
    } else if ( buttons & BUTTON_LEFT ) {
      this->left();
    } else if ( buttons & BUTTON_SELECT ) {
      this->select();
    }
  }
  this->lastButton = buttons;
  this->sheild.setCursor(0,0);
  this->screens[this->currentScreen]->loop( this->sheild );
  switch( this->currentScreen ) {
    case 1:
      this->manager.findSpecificHeat();
      this->currentScreen = 2;
    case 2: 
    {
      double *p = new double;
      *p = this->manager.getSpecificHeat();
      this->screens[2]->displayInfo( p, 1 );
      delete p;
      break;
    }
    case 4:
    {
      double *list = new double(2);
      list[0] = this->manager.getFinalTemp();
      list[1] = this->manager.getTemp();
      this->screens[4]->displayInfo( list, 2 );
      delete list;
      break;
    }
  }
}
void LCD::up() {
  this->screens[this->currentScreen]->up();
}
void LCD::down() {
  this->screens[this->currentScreen]->down();
}
void LCD::right() {
  this->screens[this->currentScreen]->right();
}
void LCD::left() {
  this->screens[this->currentScreen]->left();
}
void LCD::select() {
  int state = this->screens[this->currentScreen]->select();
  this->sheild.clear();
  if ( state > 5 ) {
    this->currentScreen = 4;
    this->manager.setTemp( (double)state );
    return;
  }
  this->currentScreen = state;
}
void LCD::displayInfo( double *list, int len, int state ) {
  this->currentScreen = state;
  this->screens[ state ]->displayInfo( list, len );
}
//// The shield uses the I2C SCL and SDA pins. On classic Arduinos
//// this is Analog 4 and 5 so you can't use those for analogRead() anymore
//// However, you can connect other I2C sensors to the I2C bus and share
//// the I2C bus.
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
//
//// These #defines make it easy to set the backlight color
//
//#define ON 0x7
//#define OFF 0x0
//
//void setup() {
//  // Debugging output
//  Serial.begin(9600);
//  // set up the LCD's number of columns and rows: 
//  lcd.begin(16, 2);
//
//  // Print a message to the LCD. We track how long it takes since
//  // this library has been optimized a bit and we're proud of it :)
//  int time = millis();
//    lcd.print("All You Can Heat");
//  lcd.setBacklight(ON);
//}
//
//
//uint8_t i=0;
//void loop() {
//      uint8_t buttons = lcd.readButtons();
//     
//      if (buttons) {
//        lcd.clear();
//        lcd.setCursor(0,0);
//        if (buttons & BUTTON_UP) {
//          lcd.print("UP ");
//          lcd.setBacklight(ON);
//        }
//        if (buttons & BUTTON_DOWN) {
//          lcd.print("DOWN ");
//          lcd.setBacklight(OFF);
//        }
//      }
//}
