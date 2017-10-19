#include "HttpHandler.h"
#include "config.h"
#include "Time.h"
#include "Util.h"
#include <ArduinoJson.h>

Util util;

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
  httpRequest = HttpRequest("POST ","/api/meting/ ");
  
  httpRequest.addRequestHeader("Host: ",serverIP);
  httpRequest.addRequestHeader("Connection: ","close");

  httpRequest.addMetingToBody(meting);

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);  
  Serial.print(" to send a meting");
  
  if (client.connect(server, 80)) {
    Serial.println("\nConnected to webserver");
    httpRequest.sendRequest(&client);
    printResponseToSerial();
  } else {
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
    Serial.println("disconnected...");

  }
}

void HttpHandler::sendSignIn() {

  httpRequest = HttpRequest("POST ", "/arne/SignIn ");

  httpRequest.addRequestHeader("Host: ", serverIP);
  httpRequest.addRequestHeader("Connection: ", "close");
  httpRequest.addRequestHeader("Content-Type: ", "application/json");

  httpRequest.addSignInToBody();

  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" for sign in");
  if (client.connect(server, 80)) {
    Serial.println("Connected to webserver");
    httpRequest.sendRequest(&client);
    saveSignInResponse();
  }
  else {
    Serial.println("Connection failed");
  }
  freeRequest();
  Serial.print("free ready");
}

void HttpHandler::parseJson(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  int id = root["Id"];
  char* ip = root["IpAddress"];
  char* name = root["Name"];

  util.writeId(id);
  util.writeIp(ip);
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
  parseJson(body);

  Serial.println();
  Serial.println(F("Response read, now we can disconnect."));
  if (!client.connected()) {
    Serial.println(F("disconnecting..."));
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
