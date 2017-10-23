#include "Time.h"
#include <Ethernet2.h>
#include <NTPClient.h>

EthernetUDP udp;
NTPClient timeClient(udp, "europe.pool.ntp.org", 7200, 60000);

void startTime() {
  timeClient.begin();
}

void updateTime() {
  Serial.print(F("\ngetting time"));
  udp.begin(8888);
  Serial.print(F("."));
  timeClient.update();
  Serial.print(F("."));
  timeClient.update();
  Serial.print(F("."));
  timeClient.update();
  Serial.print(F("."));
  timeClient.update();
  Serial.print(F("."));
  udp.stop();
  Serial.print(F(".done\n"));
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

String getFormattedString(){
  return timeClient.getFormattedTime();
}

