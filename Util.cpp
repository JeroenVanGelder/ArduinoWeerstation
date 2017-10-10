#include "Util.h"
#include <EEPROM.h>
#include <SPI.h>

Util::Util() {}

int Util::getId() {
  int ID = EEPROM.read(0);
  Serial.println(("///////////////////////////////////////////////////////////////////////"));
  Serial.println(ID);
  Serial.println(("///////////////////////////////////////////////////////////////////////"));

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
  /*
                          check if correct ip returns
  */


  return  ip;
}

void Util::writeIp(int* myIp) {
  EEPROM.write(1, myIp[0]);
  EEPROM.write(2, myIp[1]);
  EEPROM.write(3, myIp[2]);
  EEPROM.write(4, myIp[3]);
}

void Util::writeId(int id) {
  EEPROM.write(0, id);
}
