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
  
  weerstation = WeatherStation(TEMP_SENSOR);
  httpHandler = HttpHandler(); 
  httpHandler.beginEthernet();
}

void loop() {
  
  httpHandler.updateTimeFromUDP();
  
  Meting meting = weerstation.getNewMeting(getTime()); 
  
  httpHandler.sendMeting(meting);
  
  httpHandler.receiveNewConfig();
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
  delay(15000);
}

void loop() {
  
    HttpHandler httpHandler = HttpHandler();
 //   httpHandler.sendSignIn();
  //  Meting meting = {"J2","timestamp",44.3, 34.7};
    // httpHandler.sendMeting(meting);
    
      httpHandler.receiveNewConfig();

    Serial.print(F("freeMemory()="));
    Serial.println(freeMemory());
//    delay(6000);
  
}
