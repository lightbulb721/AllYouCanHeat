/*
 * @author Collin Hague
 * ExperimentManager.h
 * header for ExperimentManager.cpp
 */
 #include "HeatPad.h"
 #include "LoadCell.h"
 #include "Motor.h"
 #include "Thermistor.h"
 #ifndef EXPERIMENT_MANAGER_H
 #define EXPERIMENT_MANAGER_H
 namespace heat {
  class Manager {
    private:
      int state;
      double specificHeat;
      double previousError, intError;
      double readings[10];
      double kp, kd, ki;
      HeatPad *heatPad;
      LoadCell *loadcell;
      Motor *motor;
      Thermistor *thermistor;
      double finalTemp;
    public:
      void setTemp( double );
      double getFinalTemp();
      double getTemp();
      void findSpecificHeat();
      double getSpecificHeat();
      void stopExperiment();
      void setup();
      void loop();
      Manager( int heatPadPin, int dout, int clk, double calibrationFactor, int motorPin, int thermistorPin0, int thermistorPin1, double kp, double kd, double ki );
      Manager();
      ~Manager();
  };
 }
#endif
