#ifndef HttpHandler_h
#define HttpHandler_h

#include <Ethernet2.h>
#include "Meting.h"
#include "HttpRequest.h"
#include "Util.h"


class HttpHandler
{
  public:
    HttpHandler();
    
    void sendMeting(Meting meting);
    void beginEthernet();
    void updateTimeFromUDP();
    

    void sendSignIn();

    void receiveNewConfig();
  private:
    HttpRequest httpRequest;
    byte mac[6] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
    IPAddress ip;
    IPAddress server;
    EthernetClient client;
    Util util;

    void printResponseToSerial();
    void saveSignInResponse();
    void startTimeFromUDP();
    void freeRequest();
    void parseJson(String json);
};

#endif
