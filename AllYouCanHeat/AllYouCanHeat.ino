#include "LCD.h"
#include "Screen.h"
#include "Arduino.h"

//debug flas
#define DEBUG

#define HEATPAD 12
#define DOUT 3
#define CLK 2
#define CALIBRATIONFACTOR 1.0
#define MOTOR 13
#define THERMISTOR0 A0
#define THERMISTOR1 A1
#define KP 1
#define KD 1 
#define KI 1
#define NUMBEROFSCREENS 5

heat::SelectionScreen ss = heat::SelectionScreen();
heat::DetermineCPScreen dcps = heat::DetermineCPScreen();
heat::ShowCPScreen scps = heat::ShowCPScreen();
heat::SetTemperatureScreen sts = heat::SetTemperatureScreen();
heat::ReportTemperatureScreen rts = heat::ReportTemperatureScreen();
heat::Screen *screens[5] = { &ss, &dcps, &scps, &sts, &rts };


heat::LCD lcdDisplay = heat::LCD( screens, NUMBEROFSCREENS, HEATPAD, DOUT, CLK, CALIBRATIONFACTOR, MOTOR,THERMISTOR0, THERMISTOR1, KP, KD, KI );

//void setup() {
//  Serial.begin(9600);
//  lcdDisplay.setup();
//
//}
//
//void loop() {
//  delay(100);
//  lcdDisplay.loop();
//}
