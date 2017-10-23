#ifndef WeatherStation_h
#define WeatherStation_h
#include "Sensor.h"
#include "Meting.h"
#include "Util.h"



class WeatherStation
{
  public:
    WeatherStation();
    WeatherStation(int tempPinNr);
    Meting getNewMeting(char* metingTime);
    
    unsigned int weatherStationNameId;
    char* weatherStationIp;
    char* weatherStationName;
    
  private:
    int tempSensor;
    Util util;
    
        
};

#endif
