#include <SPI.h>
#include <Ethernet2.h>
#include <MemoryFree.h>
#include "HttpRequest.h"
#include "HttpHandler.h"
#include "Meting.h"
#include "Time.h"
#include "config.h"

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting"));
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
  //  startTime();


/*

  HttpHandler httpHandler = HttpHandler();
  //  httpHandler.sendSignIn();

  httpHandler.receiveNewConfig();

  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
*/
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
