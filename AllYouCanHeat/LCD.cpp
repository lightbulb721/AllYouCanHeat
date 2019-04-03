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

#define ON 0x7
#define OFF 0x0

using namespace heat;

LCD::LCD( Screen screens[], int screenslength ) {
  this->screens = screens;
  this->screenslength = screenslength;
  this->sheild = Adafruit_RGBLCDShield();
}

void LCD::setup() {
  this->sheild.begin( 16, 2 );
  this->sheild.print( "All You Can Heat" );
  this->sheild.setBacklight( ON );
  for( int i = 0; i < this->screenslength; i++ ) {
    this->screens[ i ].setup( this->sheild );
  }
}
void LCD::loop() {
  uint8_t buttons = this->sheild.readButtons();
  if ( buttons ) {
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
  this->screens[this->currentScreen].loop( this->sheild );
}
void LCD::up() {
  this->screens[this->currentScreen].up();
}
void LCD::down() {
  this->screens[this->currentScreen].down();
}
void LCD::right() {
  this->screens[this->currentScreen].right();
}
void LCD::left() {
  this->screens[this->currentScreen].left();
}
void LCD::select() {
  this->screens[this->currentScreen].select();
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
