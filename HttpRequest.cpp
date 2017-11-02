#include <Stepper.h>
#include <ArduinoJson.h>
#include "HttpRequest.h"

#include "config.h"

HttpRequest::HttpRequest() {}

HttpRequest::HttpRequest(char* inputMethod, char* inputPath) {
  char* protocol = "HTTP/1.1 ";
  
  int buildPathStringSize = (strlen("http://") + strlen(serverIP) + strlen(inputPath)) * sizeof(char);
  char* buildPath = malloc(buildPathStringSize);
  strcpy (buildPath, "http://");
  strcpy (buildPath, serverIP);
  strcpy (buildPath, inputPath);
  
  httpRequestLine = {inputMethod, buildPath, protocol};
  ammountOfHeaders = 0;
  bodySize = 0;
  
}

void  HttpRequest::sendRequest(EthernetClient *client) {
  sendRequestLine(client);
  
  for (int i = 0; i < ammountOfHeaders; i++) {
    sendRequestHeader(httpRequestHeader[i], client);
  }
  
  client->println(); // always one empty line between headers and content
  
  if (bodySize > 0) {
    client->println(requestBody);
    free(requestBody);
  }
  free(httpRequestLine.path);
  
}

void HttpRequest::sendRequestLine(EthernetClient *client){
  client->println();
  client->print(httpRequestLine.method);
  client->print(httpRequestLine.path);
  client->print(httpRequestLine.protocol);
  client->print("\n");
}

void HttpRequest::sendRequestHeader(HttpRequestHeader header, EthernetClient *client) {
  client->print(header.key);
  client->print(header.value);
  client->print(F("\n"));

  if(strcmp(header.key, "Content-Length: ") == 0){
    free(header.value);
  }
}

void HttpRequest::addMetingToBody(Meting inputMeting) {

  char* metingJson = util.parseMetingToJsonBody(inputMeting);

  bodySize = strlen(metingJson);

  requestBody = metingJson;

  char* sizeString = new char[4];
  itoa(bodySize, sizeString, 10);

  addRequestHeader("Content-Length: ", sizeString);
  addRequestHeader("Content-Type: ","application/json");
}

void HttpRequest::addRequestHeader(char *key, char *value) {
  httpRequestHeader[ammountOfHeaders] = HttpRequestHeader{key, value};
  if (ammountOfHeaders < HEADERSIZE) {
    ammountOfHeaders ++;
  }
}

void HttpRequest::freeRequest() {

  //DIT GEBEURT NU TIJDENS HET VERSTUREN, ZIE REGEL 24/39 (ongeveer)
  
  //free(httpRequestLine.path);
  //free(requestBody);
}

void HttpRequest::addSignInToBody() {

  // @todo free up memory after ussage
  char* signInJson;
  int ipFromEeprom = -1;
  ipFromEeprom = util.getId();

  if (ipFromEeprom != -1)
    signInJson = util.parseSignInToJsonBody(ipFromEeprom);

  bodySize = strlen(signInJson);
  requestBody = signInJson;
  
  char* sizeString = new char[4];
  
  itoa(bodySize, sizeString, 10);
  addRequestHeader("Content-Length: ", sizeString);
}

