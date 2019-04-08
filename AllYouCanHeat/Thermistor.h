#ifndef THERMISTOR_H
#define THERMISTOR_H
namespace heat {
  class Thermistor{
    private:
      double temperature;
      double resitance;
      int pin;
      double R;
    public:
      Thermistor( int pin );
      Thermistor();
      double getTemperature();
      void setup();
      void loop();
  };
}
#endif
