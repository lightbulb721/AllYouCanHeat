#ifndef LOAD_CELL_H
#define LOAD_CELL_H
#include "HX711.h"
namespace heat {
  class LoadCell {
    private:
      double mass;
      int dout;
      int clk;
      HX711 scale;
      double calibrationFactor;
    public:
      double getMass();
      void setup();
      void loop();
      LoadCell( int dout, int clk, double calibration_factor );
  };
}
#endif
