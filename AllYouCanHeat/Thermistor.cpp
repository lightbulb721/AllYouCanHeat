#include "Thermistor.h"
#include "arduino.h"
#define R0 10e3
#define DEBUG
using namespace heat;

/*
 * @function getTemperature
 * uses steinhart-hart equation for an approximation of the lookup
 * table to find the temperature instead of a lookup table.
 * @return double the temperatue that the thermistor is reading
 */
double Thermistor::getTemperature() {
  double B = 3950;
  double ans;
  ans = this->R / R0;
  ans = log( ans );
  ans /= B;
  ans += 1 / ( 298.15 );
  ans = 1 / ans;
  ans -= 273.15;  
  return ans;
}

void Thermistor::setup() {
}
void Thermistor::loop() {
  double voltage = analogRead( this->pin );
  voltage = 1023 / voltage - 1;
  this->R = R0 / voltage;
  Serial.println( this->R );
}

Thermistor::Thermistor( int pin ) {
  this->pin = pin;
}

Thermistor::Thermistor() {
  this->pin = 0;
}
