/*
 * @author Collin Hague
 * Manager class for controlling the components of the experiment
 */
#include "ExperimentManager.h"

#define DEBUG

using namespace heat;
Manager::Manager() {
  this->heatPad = new HeatPad( 0 );
  this->loadcell = new LoadCell( 0, 0, 0 );
  this->motor = new Motor( 0 );
  this->thermistor = new Thermistor[2];
  this->thermistor[0] = Thermistor( 0 );
  this->thermistor[1] = Thermistor( 0 );
  this->state = 0;
  for ( int i = 0; i < 10; i++ ) {
    this->readings[i] = 25;
  }
}
Manager::Manager( int heatPadPin, int dout, int clk, double calibrationFactor, int motorPin, int thermistorPin0, int thermistorPin1, double kp, double kd, double ki ) {
  this->heatPad = new HeatPad( heatPadPin );
  this->loadcell = new LoadCell( dout, clk, calibrationFactor );
  this->motor = new Motor( motorPin );
  this->thermistor = new Thermistor[2];
  this->thermistor[0] = Thermistor( thermistorPin0 );
  this->thermistor[1] = Thermistor( thermistorPin1 );
  this->state = 0;
  for ( int i = 0; i < 10; i++ ) {
    this->readings[i] = 25;
  }
}
Manager::~Manager() {
  delete this->heatPad;
  delete this->loadcell;
  delete this->motor;
  delete this->thermistor;
}

void Manager::setTemp( double finalTemp ) {
  this->finalTemp = finalTemp;
  state = 2;
}
double Manager::getFinalTemp() {
  return this->finalTemp;
}
double Manager::getTemp() {
  return this->thermistor[0].getTemperature();
}
void Manager::findSpecificHeat() {
  state = 1;
}
double Manager::getSpecificHeat() {
  return this->specificHeat;
}
void Manager::stopExperiment() {
  state = 0;
}
void Manager::loop() {
  switch ( this->state ) {
    case 0:
      this->motor->setVoltage( 0 );
      this->heatPad->setVoltage( 0 );
      this->intError = 0;
      this->previousError = 0;
    case 2:
      {
        //to do find time delta between loop instances
        double dt = 1;
        this->motor->setVoltage( 12 );
        double current = this->getTemp();
        double error = this->finalTemp - current;
        double derror = ( this->previousError - error ) / dt;
        this->intError += error * dt;
        double voltageOut = kp * error + kd * derror + ki * intError;
        voltageOut = voltageOut > 12 ? 12 : voltageOut;
        voltageOut = voltageOut < 0 ? 0 :voltageOut;
        this->previousError = error;
      this->heatPad->setVoltage( voltageOut );
      }
      break;
    case 1:
      {
        double dt = 1;
        double resistace = 1;
        this->motor->setVoltage( 12 );
        this->heatPad->setVoltage( 12 );
        for (int i = 9; i > 0; i-- ) {
          this->readings[ i - 1 ] = this->readings[ i ];
        }
        this->readings[9] = this->getTemp();
        this->specificHeat = ( 12 * 12 / resistace ) * 10 * dt / ( this->loadcell->getMass() * ( this->readings[0] - this->readings[9] ) );
        if ( this->getTemp() > 50 ){
          state = 0;
        }
      }
      break;
  }
}

void Manager::setup() {
  this->heatPad->setup();
  this->loadcell->setup();
  this->motor->setup();
  this->thermistor[0].setup();
  this->thermistor[1].setup();
}
