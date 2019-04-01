#include "Motor.h"
#include "Arduino.h"
using namespace heat;
void Motor::setVoltage( double voltage ) {
  this->voltage = voltage;
}
double Motor::getVoltage() {
  return this->voltage;
}
void Motor::setup() {
  
}
void Motor::loop() {
  analogWrite( this->pin, ( this->voltage / 12 ) * 255 );
}

Motor::Motor( int pin ) {
  this->pin = pin;
}

