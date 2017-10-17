#include "WeatherStation.h"
#include "Sensor.h"
WeatherStation::WeatherStation(){}

WeatherStation::WeatherStation(int tempPinNr){
  tempSensor = tempPinNr;
}
  Meting WeatherStation::getNewMeting(char* metingTime){
    Meting tempMeting = {"J2",metingTime,0, 34.7}; 
    tempMeting.Temperature = readTempValue(tempSensor);
    return tempMeting;
  }

