#include <SPI.h>
#include <Ethernet2.h>
#include "HttpRequest.h"
#include "HttpHandler.h"
#include "Meting.h"
#include "Time.h"
#include "config.h"

HttpRequest httpRequestPost("POST ","http://145.74.165.0:80/api/meting/ ","HTTP/1.1 ");
HttpHandler httpHandler;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
//  startTime();
  httpHandler = HttpHandler(httpRequestPost);
}

void loop() {
  Meting meting = {"J2","timestamp",44.3, 34.7}; 
  httpHandler.sendMeting(meting);
  
  delay(6000);
}
