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
      double getTemperature();
      void setup();
      void loop();
  };
}
#endif

