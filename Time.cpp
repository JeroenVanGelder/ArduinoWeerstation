#include "Time.h"
#include <Ethernet2.h>
#include <NTPClient.h>

EthernetUDP udp;
NTPClient timeClient(udp, "europe.pool.ntp.org", 7200, 60000);

void startTime() {
  timeClient.begin();
  updateTime();
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

char* getTime() {
  Serial.println(timeClient.getEpochTime());
  return getFormattedString();
}

char* getFormattedString(){
  return ("%ul",timeClient.getEpochTime());
}

