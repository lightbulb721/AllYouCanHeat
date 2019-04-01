/*
 * @author Collin Hague
 * ExperimentManager.h
 * header for ExperimentManager.cpp
 */
 #include "HeatPad.h"
 #include "LCD.h"
 #include "LoadCell.h"
 #include "Motor.h"
 #include "Thermistor.h"
 #ifndef EXPERIMENT_MANAGER_H
 #define EXPERIMENT_MANAGER_H
 namespace heat {
  class Manager {
    private:
      int state = 0;
      HeatPad heatPad;
      LCD lcd;
      LoadCell loadcell;
      Motor motor;
      Thermistor thermistor[2];
    public:
      void setTemp( double );
      double getTemp();
      void findSpecificHeat();
      double getSpecificHeat();
      void setup();
      void loop();
  };
 }
#endif

