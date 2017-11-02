#include "Util.h"
#include <EEPROM.h>
#include <SPI.h>
#include "config.h"

Util::Util() {}

void Util::parseGetIdJson(String json) {
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  
  if (!root.success()) {
    Serial.println(F("parseObject() failed"));
    
    return;
  }
  Serial.print(json);
  int id = root["Id"];
  char* ip = root["IpAddress"];
  char* name = root["Name"];

  writeId(id);
  writeIp(ip);
  
  //jsonBuffer.clear();
}

char* Util::parseMetingToJsonBody(Meting inputMeting) {

  char* json = new char[100];
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
  JsonObject& station = root.createNestedObject("Weatherstation");
  station["id"] = inputMeting.weatherStationId;
  root["timestamp"] = inputMeting.Timestamp;
  root["temperature"] = inputMeting.Temperature;
  root["illuminance"] = inputMeting.Illuminance;

  root.printTo(json, 100);

  return json;
}


char* Util::parseSignInToJsonBody(int getal) {
  char* json = new char[20];
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = getal;
  root.printTo(json, 20);
  //jsonBuffer.clear();
  return json;
}

int Util::getId() {
  return  EEPROM.read(0);

}

int* Util::getIp() {

  static int ip[4] = {  EEPROM.read(1),
                        EEPROM.read(2),
                        EEPROM.read(3),
                        EEPROM.read(4)
                     };
  return  ip;
}

void Util::writeIp(char* myIp) {
  char *p = myIp;
  char *str;
  int count = 1;
  while ((str = strtok_r(p, ".", &p)) != NULL) {
    EEPROM.write( count, atoi(str));
    count++;

  }

}

void Util::writeId(int id) {
  EEPROM.write(0, id);
}
