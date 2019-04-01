/*
 * @author Collin Hague
 * Manager class for controlling the components of the experiment
 */
#include "HeatPad.h"
#include "LCD.h"
#include "LoadCell.h"
#include "Motor.h"
#include "Thermistor.h"
using namespace Heat;

class Manager {
  int state = 0;
  HeatPad heatPad;
  LCD lcd;
  LoadCell loadcell;
  Motor motor;
  Thermistor[2] thermistor;

  void setTemp( double temp ) {
  }
  double getTemp() {
    
  }
  double findSpecificHeat() {
    
  }
  double getSpecificHeat() {
    
  }
  void setup() {
  }
  void loop() {
  }
}

