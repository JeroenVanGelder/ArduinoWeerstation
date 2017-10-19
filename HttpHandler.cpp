
#include "HttpHandler.h"
#include "config.h"
#include "Time.h"
HttpHandler::HttpHandler(){
  ip.fromString(arduinoIP);
  server.fromString(serverIP);
}

void HttpHandler::beginEthernet(){
  Ethernet.begin(mac, ip);
}

void HttpHandler::freeRequest(){
  httpRequest.freeRequest();
}

void HttpHandler:: startTimeFromUDP(){
  startTime();
}
void HttpHandler:: updateTimeFromUDP(){
  updateTime();
}

void HttpHandler::sendMeting(Meting meting){
  httpRequest = HttpRequest("POST ","/api/meting/ ");
  
  httpRequest.addRequestHeader("Host: ",serverIP);
  httpRequest.addRequestHeader("Connection: ","close");

  httpRequest.addMetingToBody(meting);

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);  
  
  if (client.connect(server, 80)) {
    Serial.println("\nConnected to webserver");
    httpRequest.sendRequest(&client);
    printResponseToSerial();
  }else {
    Serial.println("Connection failed");
  }
  
  freeRequest();
}

void HttpHandler::printResponseToSerial(){
  while (!client.available()) {
      delay(5); // let's take five. Here we should check for time out
      Serial.print(".");
    }
    Serial.println("Response received:");
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      delay(1); // give input some time do to it's thingpie.
    }
    Serial.println();
    Serial.println("Response read, now we can disconnect.");
    if (!client.connected()) {
      Serial.println("disconnecting...");
      client.stop();
    }
}

