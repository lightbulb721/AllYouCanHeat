#include "LoadCell.h"
#include "HX711.h"
using namespace heat;
LoadCell::LoadCell( int dout, int clk, double calibration_factor ) {
  this->dout = dout;
  this->clk = clk;
  this->calibration_factor = calibration_factor;
}

void LoadCell::setup() {
  this->scale.begin( this->dout, this->clk );
  this->scale.set_scale( this->calibration_factor );
  this->scale.tare();
}

void LoadCell::loop() {
  this->mass = scale.get_units();
}

