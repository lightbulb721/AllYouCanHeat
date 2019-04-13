#include "HeatPad.h"
#include "Arduino.h"
/*
 * @author Collin Hague
 * controls the heat pad
 */

#define DEBUG

using namespace heat;

void HeatPad::setVoltage( double voltage ) {
  this->voltage = voltage;
}

double HeatPad::getVoltage() {
  return this->voltage;
}

void HeatPad::setup() {
  pinMode( 9, OUTPUT );
}
void HeatPad::loop() {
  Serial.print( "analogWrite( " );
  Serial.print( this->pin );
  Serial.print( ", " );
  Serial.print( (this->voltage / 12) * 255 );
  Serial.println( " )" );
  analogWrite( 9, ( this->voltage / 12 ) * 255 );
}

HeatPad::HeatPad( int pin ) {
  this->pin = pin;
  this->voltage = 0;
}
