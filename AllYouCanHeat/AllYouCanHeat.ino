#include "LCD.h"
#include "Screen.h"
using namespace heat;


#define HEATPAD 0
#define DOUT 0
#define CLK 0
#define CALIBRATIONFACTOR 0
#define MOTOR 0
#define THERMISTOR0 0
#define THERMISTOR1 0
#define KP 1
#define KD 1 
#define KI 1
#define NUMBEROFSCREENS 5

Screen screens[5] = { SelectionScreen(), DetermineCPScreen(), ShowCPScreen(), SetTemperatureScreen(), ReportTemperatureScreen() };


LCD lcdDisplay = LCD( screens, NUMBEROFSCREENS, HEATPAD, DOUT, CLK, CALIBRATIONFACTOR, MOTOR,THERMISTOR0, THERMISTOR1, KP, KD, KI );

void setup() {
  lcdDisplay.setup();

}

void loop() {
  lcdDisplay.loop();
}
