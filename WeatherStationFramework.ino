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
  Serial.println("Starting");
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
//  startTime();
  
}

void loop() {
  HttpHandler httpHandler = HttpHandler();
  Meting meting = {"J2","timestamp",44.3, 34.7}; 
  httpHandler.sendMeting(meting);
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  delay(6000);
}
