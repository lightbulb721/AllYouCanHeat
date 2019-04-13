/////*********************
////This code is for the UI
////LCD uses:
////5v
////GND
////20SDA
////21SCL
////**********************/
////
//// include the library code:
//#include <Wire.h>
//#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
//#include "Arduino.h"
//
//
//// The shield uses the I2C SCL and SDA pins. On classic Arduinos
//// this is Analog 4 and 5 so you can't use those for analogRead() anymore
//// However, you can connect other I2C sensors to the I2C bus and share
//// the I2C bus.
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
//
//// These #defines set the backlight
//
//#define ON 0x7
//#define OFF 0x0
//
//void setup() {
//  // set up the LCD's number of columns and rows: 
//  lcd.begin(16, 2);
//  // turns on LCD
//  lcd.print("CP    HEAT   OFF");
//  lcd.setBacklight(ON);
//  lcd.setCursor(0,1);
//  lcd.blink();
//}
//
//uint8_t i=0;
//void loop() {
//      uint8_t buttons = lcd.readButtons();
//     
//      if (buttons) {
//        lcd.clear();
//        //cursors HEAT
//        if (buttons & BUTTON_RIGHT) {
//        lcd.print("CP    HEAT   OFF");
//        lcd.setCursor(8,1);
//        }
//        //cursors CP
//        if (buttons & BUTTON_LEFT) {
//        lcd.print("CP    HEAT   OFF");
//        lcd.setCursor(0,1);
//
//        }
//      }
//}
