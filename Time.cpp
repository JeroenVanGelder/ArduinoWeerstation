#include "Time.h"
#include <Ethernet2.h>
#include <NTPClient.h>

EthernetUDP udp;
NTPClient timeClient(udp, "europe.pool.ntp.org", 7200, 60000);

void startTime() {
  timeClient.begin();
}

void updateTime() {
  timeClient.update();
  timeClient.update();
  timeClient.update();
  timeClient.update();
}
void endTime() {
  timeClient.end();
}

String getTime() {
  return timeClient.getFormattedTime();
}

char* getFormattedString(){
  return "2015-09-22T19:14:55.7482026Z";
}

