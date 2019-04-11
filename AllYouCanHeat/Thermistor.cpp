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
  double invT = 1 / 298.15 + ( 1 / B ) * log( this->R / R0 );
  return (1 / invT) - 273.15;
}

void Thermistor::setup() {
}
void Thermistor::loop() {
  double voltage = analogRead( this->pin );
  this->R = R0 * voltage /( 1023 - voltage );
}

Thermistor::Thermistor( int pin ) {
  this->pin = pin;
}

Thermistor::Thermistor() {
  this->pin = 0;
}
