#include <SPI.h>
#include <Ethernet2.h>
#include <MemoryFree.h>
#include "HttpRequest.h"
#include "HttpHandler.h"
#include "Meting.h"
#include "Time.h"
#include "config.h"
#include "WeatherStation.h"

WeatherStation weerstation;
HttpHandler httpHandler;

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("Starting"));
  
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
  
  httpHandler = HttpHandler(); 
  
  httpHandler.beginEthernet();
  
  httpHandler.sendSignIn();

  weerstation = WeatherStation(TEMP_SENSOR);
}

void loop() {
  
  //httpHandler.receiveNewConfig();
  httpHandler.updateTimeFromUDP();
  
  Meting meting = weerstation.getNewMeting(getTime()); 
  
  httpHandler.sendMeting(meting);
  
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
  delay(60000);
//  
}
