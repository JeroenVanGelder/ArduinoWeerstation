#include "Time.h"
#include <Ethernet2.h>
#include <NTPClient.h>

EthernetUDP udp;
NTPClient timeClient(udp, "europe.pool.ntp.org", 7200, 60000);

void startTime() {
  timeClient.begin();
}

void updateTime() {
  udp.begin(8888);
  timeClient.update();
  timeClient.update();
  timeClient.update();
  timeClient.update();
  udp.stop();
#ifdef DEBUG
  Serial.print(F("got time\n"));
#endif
}

void endTime() {
  timeClient.end();
}

char* getTime() {
  String timeString = getFormattedString();
  char timeCharArray[10];
  strcpy(timeCharArray, timeString.c_str());
  return timeCharArray;
}

String getFormattedString() {
  return timeClient.getFormattedTime();
}

