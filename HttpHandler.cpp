
#include "HttpHandler.h"
#include "config.h"

HttpHandler::HttpHandler(){

}

HttpHandler::HttpHandler(HttpRequest inputRequest){
  httpRequest = inputRequest;
  //mac = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
  ip = IPAddress(10,42,0,2);
  server = IPAddress(192,168,2,68);
  Ethernet.begin(mac, ip);
}

void HttpHandler::sendMeting(Meting meting){
  
  httpRequest = HttpRequest("POST ","http://192.168.2.68:80/api/meting/ ","HTTP/1.1 ");
  
  httpRequest.addRequestHeader("Host: ",serverIP);
  httpRequest.addRequestHeader("Connection: ","close");
  httpRequest.addRequestHeader("Content-Type: ","application/json");
  
  httpRequest.addMetingToBody(meting);

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);  
  if (client.connect(server, 80)) {
    
    Serial.println("Connected to webserver");

//    //Test for Post
    httpRequest.sendRequest(client);
    printResponseToSerial();
  }
  else {
    Serial.println("Connection failed");
  }
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

