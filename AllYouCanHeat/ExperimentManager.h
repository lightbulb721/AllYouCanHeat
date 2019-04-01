/*
 * @author Collin Hague
 * ExperimentManager.h
 * header for ExperimentManager.cpp
 */
 namespace heat {
  class Manager {
    public:
      void setTemp( double );
      double getTemp();
      void findSpecificHeat();
      double getSpecificHeat();
      void setup();
      void loop();
  }
 }

