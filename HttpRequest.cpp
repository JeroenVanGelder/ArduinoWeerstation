#include "HttpRequest.h"
#include <string.h>

HttpRequest::HttpRequest(char inputMethod[20], char inputPath[100], char inputProtocol[10]){
  httpRequestLine = {inputMethod, inputPath, inputProtocol};
  ammountOfHeaders = 0;
  bodySize = 0;
}

HttpRequest::HttpRequest(char inputMethod[20], char inputPath[100], char inputProtocol[10], char *inputRequestBody){
  httpRequestLine = {inputMethod, inputPath, inputProtocol};
  requestBody = inputRequestBody;
  ammountOfHeaders = 0;
  bodySize = 0;
}

void  HttpRequest::sendRequest(EthernetClient client){
  client.println();
  client.print(httpRequestLine.method);
  client.print(httpRequestLine.path);
  client.print(httpRequestLine.protocol);
  client.print("\n");
  
  for(int i = 0; i < ammountOfHeaders; i++){
    sendRequestHeader(httpRequestHeader[i], client);    
  }
  client.println(); // always one empty line between headers and content
  
  if(bodySize > 0){
    client.println(requestBody); 
    
  }
}

void HttpRequest::sendRequestHeader(HttpRequestHeader header, EthernetClient client){
    client.print(header.key);
    client.print(header.value);
    client.print("\n");
}

void HttpRequest::parseMetingToJsonBody(Meting inputMeting){
  requestBody="{\"weatherstation\": \"J1\",\"temperature\": 25.4,\"illuminance\": 66.6}\n";
  bodySize=1;
}

void HttpRequest::addRequestHeader(char *key, char *value){
  httpRequestHeader[ammountOfHeaders] = HttpRequestHeader{key,value};
  if(ammountOfHeaders < HEADERSIZE);
    ammountOfHeaders ++;
}

