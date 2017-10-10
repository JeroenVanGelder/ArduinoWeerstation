#ifndef HttpRequest_h
#define HttpRequest_h
#define HEADERSIZE 20

#include <Ethernet2.h>
#include "Meting.h"

class HttpRequest
{
  public:
    HttpRequest();
    HttpRequest(char* inputMethod, char* inputPath, char* inputProtocol);
        
    void addRequestHeader(char *key, char* value);
    void sendRequest(EthernetClient *client);
    void addMetingToBody(Meting inputMeting);
    void freeRequest();
    
  private:
    struct HttpRequestLine {
      char *method;
      char *path;
      char *protocol;
    } httpRequestLine;

    struct HttpRequestHeader{
      char *key;
      char *value;
    } httpRequestHeader[HEADERSIZE];

    char *requestBody;

    int ammountOfHeaders;
    int bodySize;
    
    void addRequestBodyLine(char *inputRequestBodyLine);
    void sendRequestHeader(HttpRequestHeader header, EthernetClient *client);
    char* parseMetingToJsonBody(Meting inputMeting);
    
    
};

#endif
