#include "HttpHandler.h"
#include "config.h"
#include "Time.h"
#include "Util.h"
#include <ArduinoJson.h>

//#define DEBUG 1

HttpHandler::HttpHandler() {
  ip.fromString(arduinoIP);
  server.fromString(serverIP);
}

void HttpHandler::beginEthernet() {
  Ethernet.begin(mac, ip);
}

void HttpHandler::freeRequest() {
  httpRequest.freeRequest();
}

void HttpHandler:: startTimeFromUDP() {
  startTime();
}
void HttpHandler:: updateTimeFromUDP() {
  updateTime();
}

void HttpHandler::sendMeting(Meting meting) {

  HttpRequest metingHttpRequest = buildRequestForSendMeting(meting);

  if (client.connect(server, 80)) {

#ifdef DEBUG
    Serial.println(F("\nConnected to webserver"));
#endif

    metingHttpRequest.sendRequest(&client);

#ifdef DEBUG
    printResponseToSerial();

#endif
    stopConnection();
  } else {

#ifdef DEBUG
    Serial.println(F("\nConnection failed"));
#endif
  }

  freeRequest();
}

HttpRequest HttpHandler::buildRequestForSendMeting(Meting meting) {
  HttpRequest returnHttpRequest = HttpRequest("POST ", "/api/meting/ ");

  returnHttpRequest.addRequestHeader("Host: ", serverIP);
  returnHttpRequest.addRequestHeader("Connection: ", "close");

  returnHttpRequest.addMetingToBody(meting);

  return returnHttpRequest;
}

void HttpHandler::printResponseToSerial() {
  while (!client.available()) {
    delay(5); // let's take five. Here we should check for time out
  }
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
    delay(1); // give input some time do to it's thingpie.
  }
}

void HttpHandler::stopConnection() {
  if (!client.connected()) {
    client.stop();
#ifdef DEBUG
    Serial.println(F("disconnected..."));
#endif

  }
}

void HttpHandler::sendSignIn() {

  httpRequest = HttpRequest("POST ", "/SignIn ");

  httpRequest.addRequestHeader("Host: ", serverIP);
  httpRequest.addRequestHeader("Connection: ", "close");
  httpRequest.addRequestHeader("Content-Type: ", "application/json");

  httpRequest.addSignInToBody();

  if (client.connect(server, 80)) {
#ifdef DEBUG
    Serial.println(F("Connected to webserver"));
#endif
    httpRequest.sendRequest(&client);

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
#ifdef DEBUG
    Serial.print(F("."));
#endif

  }
#ifdef DEBUG
  Serial.println(F("Response received:"));
#endif

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
#ifdef DEBUG
    Serial.println(F("disconnected..."));
#endif
  }
}
