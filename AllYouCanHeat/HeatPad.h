#ifndef HEAT_PAD_H
#define HEAT_PAD_H
namespace heat{
  class HeatPad {
    private:
      double voltage;
      int pin;
    public:
      void setVoltage( double );
      double getVoltage();
      void loop();
      void setup();
      HeatPad( int pin );
  };
}
#endif
