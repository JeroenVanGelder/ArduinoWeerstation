#include "HttpHandler.h"
#include "config.h"
#include "Time.h"
#include "Util.h"
#include <ArduinoJson.h>

HttpHandler::HttpHandler() {
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
  
  HttpRequest metingHttpRequest = buildRequestForSendMeting(meting);
  
  if (client.connect(server, 80)) {
    Serial.println(F("\nConnected to webserver"));
    metingHttpRequest.sendRequest(&client);
    printResponseToSerial();
    stopConnection();
  } else {
    Serial.println(F("\nConnection failed"));
  }
  
  freeRequest();
}

HttpRequest HttpHandler::buildRequestForSendMeting(Meting meting){
  HttpRequest returnHttpRequest = HttpRequest("POST ","/api/meting/ ");
  
  returnHttpRequest.addRequestHeader("Host: ",serverIP);
  returnHttpRequest.addRequestHeader("Connection: ","close");

  returnHttpRequest.addMetingToBody(meting);

  return returnHttpRequest;
}
 
void HttpHandler::printResponseToSerial(){
  while (!client.available()) {
    delay(5); // let's take five. Here we should check for time out
  }
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
    delay(1); // give input some time do to it's thingpie.
  }
}

void HttpHandler::stopConnection(){
  if (!client.connected()) {
    client.stop();
    Serial.println(F("disconnected..."));
  }
}

void HttpHandler::sendSignIn() {

  httpRequest = HttpRequest("POST ", "/SignIn ");

  httpRequest.addRequestHeader("Host: ", serverIP);
  httpRequest.addRequestHeader("Connection: ", "close");
  httpRequest.addRequestHeader("Content-Type: ", "application/json");

  httpRequest.addSignInToBody();

  if (client.connect(server, 80)) {
    Serial.println(F("Connected to webserver"));
    httpRequest.sendRequest(&client);
    //printResponseToSerial();
    saveSignInResponse();
  }
  else {
    Serial.println(F("Connection failed"));
  }
  freeRequest();
}

void HttpHandler::saveSignInResponse() {
  while (!client.available()) {
    delay(5); // let's take five. Here we should check for time out
    Serial.print(F("."));
  }
  Serial.println(F("Response received:"));

  bool bodyIsHere = false;
  String body;
  char newRule;
  while (client.available()) {
    char   c = client.read();
    
    if (bodyIsHere)
      body += c;

    if (c == '\r')
      if (newRule == '\n')
        bodyIsHere = true;
        
    newRule = c;

    delay(1); // give input some time do to it's thingpie.
  }
  
  util.parseGetIdJson(body);

  if (!client.connected()) {
    client.stop();
    Serial.println(F("disconnected..."));

  }
}

void HttpHandler::receiveNewConfig() {

  Ethernet.begin(mac, ip);
  Serial.println(Ethernet.localIP());

  EthernetServer ConfigServer(80);
  ConfigServer.begin();

  EthernetClient ConfigClient = ConfigServer.available();
  Serial.println(ConfigClient);
  while (!ConfigClient) {}
  if (ConfigClient) {
    Serial.println("if");

    while (ConfigClient.connected()) {
      Serial.println("while");
      if (ConfigClient.available()) {


        Serial.print(ConfigClient.read());
      }
      ConfigClient.println("HTTP/1.1 404 OK");
      ConfigClient.println("Content-Type: text/html");
      ConfigClient.println("Connnection: close");
      ConfigClient.println();
      ConfigClient.println("<!DOCTYPE HTML>");
      ConfigClient.println("<html><body>foutje</body></html>");
    }


  }
  delay(1);

  ConfigClient.stop();
  Serial.println("Client disonnected");
}
