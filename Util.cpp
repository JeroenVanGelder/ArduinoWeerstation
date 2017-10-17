#include "Util.h"
#include <EEPROM.h>
#include <SPI.h>

Util::Util() {}

int Util::getId() {
  int ID = EEPROM.read(0);
  if (ID >= 0 and ID < 256)
    return ID;

  return 0;
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
