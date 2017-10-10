#include "Time.h"
#include <Ethernet2.h>
#include <NTPClient.h>

EthernetUDP udp;
NTPClient timeClient(udp, "europe.pool.ntp.org", 7200, 60000);

void startTime() {
  Serial.print("getting time, ");
  timeClient.begin();
  Serial.print("got time, ");
  updateTime();
  Serial.print("updated time\n");
}

void updateTime() {
//  timeClient.update();
//  timeClient.update();
//  timeClient.update();
//  timeClient.update();
}

void endTime() {
  timeClient.end();
}

char* getTime() {
  return getFormattedString();
}

char* getFormattedString(){
  return ("%ul",timeClient.getEpochTime());
}

