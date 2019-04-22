/*
 * @author Collin Hague
 * Manager class for controlling the components of the experiment
 */
#include "ExperimentManager.h"

#define DEBUG

using namespace heat;

 void simpLinReg(float* x, float* y, float* lrCoef, int n){
  // pass x and y arrays (pointers), lrCoef pointer, and n.  The lrCoef array is comprised of the slope=lrCoef[0] and intercept=lrCoef[1].  n is length of the x and y arrays.
  // http://en.wikipedia.org/wiki/Simple_linear_regression

  // initialize variables
  float xbar=0;
  float ybar=0;
  float xybar=0;
  float xsqbar=0;
  
  // calculations required for linear regression
  for (int i=0; i<n; i++){
    xbar=xbar+x[i];
    ybar=ybar+y[i];
    xybar=xybar+x[i]*y[i];
    xsqbar=xsqbar+x[i]*x[i];
  }
  xbar=xbar/n;
  ybar=ybar/n;
  xybar=xybar/n;
  xsqbar=xsqbar/n;
  
  // simple linear regression algorithm
  lrCoef[0]=(xybar-xbar*ybar)/(xsqbar-xbar*xbar);
  lrCoef[1]=ybar-lrCoef[0]*xbar;
}





Manager::Manager() {
  this->heatPad = new HeatPad( 0 );
  this->loadcell = new LoadCell( 0, 0, 0 );
  this->motor = new Motor( 0 );
  this->thermistor = new Thermistor[2];
  this->thermistor[0] = Thermistor( 0 );
  this->thermistor[1] = Thermistor( 0 );
  this->state = 0;
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
  this->kp = kp;
  this->kd = kd;
  this->ki = ki;
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
  if ( millis() - this->t0 < 5000 ) {
    this->loadcell->tare();
  }
  switch ( this->state ) {
    /*
     * State 0 is the no nothing state turns everything off
     */
    case 0:
      this->motor->setVoltage( 0 );
      this->heatPad->setVoltage( 0 );
      this->intError = 0;
      this->previousError = 0;
      this->readingsCount = 0;
      for ( int i = 0; i < 60; i++ ) {
        this->readings[i] = 25;
        this->times[i] = float(i);
      }
      break;
      /*
       * case 2 is the hold temperature state has the pid controller
       * The pid is currently untuned clamps the voltage between 0 and 12
       */
    case 2:
      {
        //to do find time delta between loop instances
        double dt = 0.1;
        this->motor->setVoltage( 12 );
        double current = this->getTemp();
        double error = this->finalTemp - current;
        double derror = ( this->previousError - error ) / dt;
        this->intError += error * dt;
        double voltageOut = error * this->kp + derror * this->kd + this->intError * this->ki;
        voltageOut = voltageOut > 12 ? 12 : voltageOut;
        voltageOut = voltageOut < 0 ? 0 :voltageOut;
        this->previousError = error;
        this->heatPad->setVoltage( voltageOut );
        Serial.println( voltageOut );
      }
      break;
      /*
       * case 1 is the find cp
       * uses time delta of .1s
       * the resistance of the heatpad still needs to be found the variable needs to be updated
       * the motor enery has not been added to the heat variable
       * automatically turns off when T > 50C
       * uses a time delta of 1s 10 reads apart
       */
    case 1:
      {
        double dt = .1;
        double resistace = 22;
        this->motor->setVoltage( 12 );
        this->heatPad->setVoltage( 12 );
        if ( this->readingsCount >= 10 ) {
          for (int i = 0; i <59; i++ ) {
            this->readings[i] = this->readings[ i + 1 ];
            this->times[i] = this->times[i+1];
          }
          this->times[59] = millis() / 1000;
          this->readings[59] = this->getTemp();
          this->readingsCount = 0;
          for ( int i = 0; i < 60; i++ ) {
            Serial.print( this->readings[i] );
            Serial.print( " " );
          }
          Serial.print("\n");
          for ( int i = 0; i < 60; i++ ) {
            Serial.print( this->times[i] );
            Serial.print( " " );
          }
          Serial.print("\n");
        } else {
          this->readingsCount++;
        }
        //add heat from motor
        double heat = 12 * 12 / resistace * 2; //+ motor energy;
        float coef[2] = {0,0};
        simpLinReg( this->times, this->readings, coef, 60 );
        Serial.print( coef[0] );
        Serial.print( " " );
        Serial.println( coef[1] );
        this->specificHeat = heat / ( this->loadcell->getMass() * coef[0] );
        //shuts off when temperature is greater than 50C
        Serial.println( this->specificHeat);
        if ( this->getTemp() > 50 ){
          state = 0;
        }
      }
      break;
  }
  this->heatPad->loop();
  this->motor->loop();
  this->loadcell->loop();
  this->thermistor[0].loop();
  this->thermistor[1].loop();
  //output to serial  Serial.print( "State: " );
  Serial.print( this->state );
  Serial.print( " Heating Voltage: " );
  Serial.print( this->heatPad->getVoltage() );
  Serial.print( " Motor Voltage: " );
  Serial.print( this->motor->getVoltage() );
  Serial.print( " Mass: " );
  Serial.print( this->loadcell->getMass() );
  Serial.print( " T0: " );
  Serial.print( this->thermistor[0].getTemperature() );
  Serial.print( " T1: " );
  Serial.println( this->thermistor[1].getTemperature() );
}

void Manager::setup() {
  this->heatPad->setup();
  this->loadcell->setup();
  this->motor->setup();
  this->thermistor[0].setup();
  this->thermistor[1].setup();
  this->t0 = millis();
}
