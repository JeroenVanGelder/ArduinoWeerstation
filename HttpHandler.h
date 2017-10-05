#ifndef HttpHandler_h
#define HttpHandler_h

#include <Ethernet2.h>
#include "Meting.h"
#include "HttpRequest.h"

class HttpHandler
{
  public:
    HttpHandler();
    HttpHandler(HttpRequest inputRequest);
    
    void sendMeting(Meting meting);
    
  private:
    HttpRequest httpRequest;
    byte mac[6] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
    IPAddress ip;
    IPAddress server;
    EthernetClient client;

    void printResponseToSerial();
    void freeRequest();
};

#endif
