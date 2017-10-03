#include <SPI.h>
#include <Ethernet2.h>
#include "HttpRequest.h"
#include "Meting.h"
// check your ethernet shield
// Make sure it's unique
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
IPAddress ip(10,42,0,2); // IP of Arduino (web client)

//School
IPAddress server(145,74,164,95); // IP2 of webserver
HttpRequest httpRequestGet("GET ","http://145.74.164.95:80/api/meting/ ","HTTP/1.1 ");
HttpRequest httpRequestPost("POST ","http://145.74.164.95:80/api/meting/ ","HTTP/1.1 ");
char* ipServer = "145.74.164.95";

////Thuis
//IPAddress server(192,168,2,68); // IP2 of webserver
//HttpRequest httpRequestGet("GET ","http://192.168.2.68:80/api/meting/ ","HTTP/1.1 ");
//HttpRequest httpRequestPost("POST ","http://192.168.2.68:80/api/meting/ ","HTTP/1.1 ");
//char* ipServer = "192.168.2.68";

Meting meting = {"J1", 21.3, 60.7}; 

EthernetClient client;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Serial.println("Starting");
  
  //Setup for Test for Get
  httpRequestGet.addRequestHeader("Host: ",ipServer);
  httpRequestGet.addRequestHeader("Connection: ","close");

  //Setup for Test for Post
  httpRequestPost.addRequestHeader("Host: ",ipServer);
  httpRequestPost.addRequestHeader("Connection: ","close");
  httpRequestPost.addRequestHeader("Content-Type: ","application/json");
  httpRequestPost.addRequestHeader("Content-Length: ","64");
  httpRequestPost.parseMetingToJsonBody(meting);
}

void loop() {
  Serial.println("\n");
  Serial.println("Connecting...");
    
  if (client.connect(server, 80)) {
    
    Serial.println("Connected to webserver");
    //Test for Get
//    httpRequestGet.sendRequest(client);
//    getResponse();

//    //Test for Post
    httpRequestPost.sendRequest(client);
    getResponse();
  }
  else {
    Serial.println("Connection failed");
  }
  
  Serial.println("The end. Now wait for 1 minute");
  delay(60000);

}

void getResponse(){
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
    Serial.println("We are disconnected");
}

