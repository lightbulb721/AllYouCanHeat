#include <Adafruit_RGBLCDShield.h>

#include "LCD.h"
#include "Screen.h"
#include "Arduino.h"


/*
 * ===================================================================
 * important code section ExperimentManager.cpp line 63
 * the manager.loop function has the logic for the different experiments
 * ===================================================================
 */
//debug flas
#define DEBUG

#define HEATPAD 9
#define DOUT 3
#define CLK 2
#define CALIBRATIONFACTOR 391200
#define MOTOR 13
#define THERMISTOR0 A0
#define THERMISTOR1 A1
#define KP 1.0
#define KD 1.0 
#define KI 1.0
#define NUMBEROFSCREENS 5

heat::SelectionScreen ss = heat::SelectionScreen();
heat::DetermineCPScreen dcps = heat::DetermineCPScreen();
heat::ShowCPScreen scps = heat::ShowCPScreen();
heat::SetTemperatureScreen sts = heat::SetTemperatureScreen();
heat::ReportTemperatureScreen rts = heat::ReportTemperatureScreen();
heat::Screen *screens[5] = { &ss, &dcps, &scps, &sts, &rts };


heat::LCD lcdDisplay = heat::LCD( screens, NUMBEROFSCREENS, HEATPAD, DOUT, CLK, CALIBRATIONFACTOR, MOTOR,THERMISTOR0, THERMISTOR1, KP, KD, KI );

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  lcdDisplay.setup();

}

void loop() {
  delay(100);
  lcdDisplay.loop();
}

////thermistor test
//heat::Thermistor t0 = heat::Thermistor( THERMISTOR0 );
//void setup() {
//  Serial.begin(9600);
//  t0.setup();
//}
//void loop() {
//  delay(500);
//  t0.loop();
//  Serial.println(t0.getTemperature() );
//}

////Motor test
//heat::Motor m = heat::Motor(MOTOR);
//
//void setup() {
//  Serial.begin( 9600 );
//  m.setup();
//  m.setVoltage(12);
//}
//void loop() {
//  Serial.println( "12V" );
//  m.loop();
//}

////load cell test
//heat::LoadCell lc = heat::LoadCell( DOUT, CLK, CALIBRATIONFACTOR);
//void setup() {
//  Serial.begin( 9600 );
//  lc.setup();
//}
//
//void loop() {
//  delay(500);
//  Serial.print( lc.getMass() );
//  Serial.print("\n");
//}
//
////HeatPad test
//heat::HeatPad hp = heat::HeatPad( HEATPAD );
//void setup() {
//  hp.setup();
//  hp.setVoltage(0);
//  Serial.begin(9600);
//}
//
//void loop() {
//  delay(500);
//  hp.setVoltage(12);
//  hp.loop();
//  Serial.println( hp.getVoltage() );
//}

