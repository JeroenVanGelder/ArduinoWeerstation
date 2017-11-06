#include "WeatherStation.h"
#include "Sensor.h"
#include "config.h"

WeatherStation::WeatherStation(){}

WeatherStation::WeatherStation(int tempPinNr, int illuPinNr){
  tempSensor = tempPinNr;
  illuSensor = illuPinNr;
  weatherStationNameId = util.getId();
  weatherStationIp = arduinoIP;
  weatherStationName = "EMPTY";
  //Weatherstation ip, id en name worden nog niet gebruikt. Ze moeten worden opgeruimd of via de juiste functies worden aangeroepen.
}

  Meting WeatherStation::getNewMeting(char* metingTime){
    Meting tempMeting = {weatherStationNameId,metingTime,0, 34.7}; 
    tempMeting.Temperature = readTempValue(tempSensor);
    tempMeting.Illuminance = readLightDepedentResistor(illuSensor);
    return tempMeting;
  }

