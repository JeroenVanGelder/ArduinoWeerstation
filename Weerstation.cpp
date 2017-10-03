#include "Weerstation.h"

Weerstation::Weerstation(char* name) {
  _name = name;
}

Meting Weerstation::getMeting() {
  return {
    _name,
    getFormattedString(),
    readTempValue(-1),
    readLightDepedentResistor(-1)
  };
}
