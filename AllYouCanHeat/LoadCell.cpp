#include "LoadCell.h"
#include "HX711.h"
#define DEBUG
using namespace heat;
LoadCell::LoadCell( int dout, int clk, double calibrationFactor ) {
  this->dout = dout;
  this->clk = clk;
  this->calibrationFactor = calibrationFactor;
}

void LoadCell::setup() {
  this->scale.begin( this->dout, this->clk );
  this->scale.set_scale( this->calibrationFactor );
  this->scale.tare();
}

void LoadCell::loop() {
  this->mass = scale.get_units();
}

double LoadCell::getMass() {
  return mass;
}
