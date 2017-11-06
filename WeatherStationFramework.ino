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

#ifdef DEBUG
  Serial.println(F("Starting"));
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
#endif

  httpHandler = HttpHandler();

  httpHandler.beginEthernet();

  httpHandler.sendSignIn();

  weerstation = WeatherStation(TEMP_SENSOR, ILLU_SENSOR);
}

void loop() {
  httpHandler.updateTimeFromUDP();

  Meting meting = weerstation.getNewMeting(getTime());

  httpHandler.sendMeting(meting);

#ifdef DEBUG
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
#endif

  delay(50000);
  
}
