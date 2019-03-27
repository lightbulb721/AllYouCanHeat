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
  Thermistor thermistor0;
  Thermistor thermistor1;

  void setup(void) {
  }
  void loop(void) {
  }
}

