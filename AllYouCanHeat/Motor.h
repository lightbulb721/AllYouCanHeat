#ifndef MOTOR_H
#define MOTOR_H
namespace heat {
  class Motor {    
    private:
      double voltage;
      int pin;
    public:
      void setVoltage( double );
      double getVoltage();
      void setup();
      void loop();
      Motor( int pin );
  };
}
#endif

