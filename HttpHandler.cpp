
#include "HttpHandler.h"
#include "config.h"

HttpHandler::HttpHandler(){
  ip.fromString(arduinoIP);
  server.fromString(serverIP);
  Ethernet.begin(mac, ip);
}

HttpHandler::HttpHandler(HttpRequest inputRequest) {
  httpRequest = inputRequest;
  ip.fromString(arduinoIP);
  server.fromString(serverIP);
  Ethernet.begin(mac, ip);
}

void HttpHandler::sendMeting(Meting meting){
  httpRequest = HttpRequest("POST ","/api/meting/ ","HTTP/1.1 ");
  
  httpRequest.addRequestHeader("Host: ",serverIP);
  httpRequest.addRequestHeader("Connection: ","close");
  
  httpRequest.addMetingToBody(meting);

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);
  if (client.connect(server, 80)) {

    Serial.println("Connected to webserver");

    //    //Test for Post
    httpRequest.sendRequest(&client);
    printResponseToSerial();
  }else {
    Serial.println("Connection failed");
  }
  
  freeRequest();
}

void HttpHandler::freeRequest() {
  httpRequest.freeRequest();
}

void HttpHandler::printResponseToSerial() {
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
      Serial.println("disconnected...");

  }
}

/*
   temp for sign in functionaliteit

*/

void HttpHandler::sendSignIn() {

  httpRequest = HttpRequest("POST ", "http://192.168.137.1/arne/SignIn ", "HTTP/1.1 ");

  httpRequest.addRequestHeader("Host: ", serverIP);
  httpRequest.addRequestHeader("Connection: ", "close");
  httpRequest.addRequestHeader("Content-Type: ", "application/json");

  httpRequest.addSignInToBody();

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);
  if (client.connect(server, 80)) {

    Serial.println("Connected to webserver");

    //    //Test for Post
    httpRequest.sendRequest(&client);
    printResponseToSerial();
//    util.writeId(13);
  }
  else {
    Serial.println("Connection failed");
  }
  freeRequest();
  Serial.print("free ready");
}
