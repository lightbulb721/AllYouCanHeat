#include "HeatPad.h"
#include "Arduino.h"
/*
 * @author Collin Hague
 * controls the heat pad
 */
using namespace heat;

void HeatPad::setVoltage( double voltage ) {
  this->voltage = voltage;
}

double HeatPad::getVoltage() {
  return this->voltage;
}

void HeatPad::setup() {
}
void HeatPad::loop() {
  analogWrite( this->pin, ( this->voltage / 12 ) * 255 );
}

HeatPad::HeatPad( int pin ) {
  this->pin = pin;
}

