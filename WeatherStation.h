#ifndef WeatherStation_h
#define WeatherStation_h
#include "Sensor.h"
#include "Meting.h"

class WeatherStation
{
  public:
    WeatherStation();
    WeatherStation(int tempPinNr);
    Meting getNewMeting(char* metingTime);
    
  private:
    int tempSensor;
    
        
};

#endif
