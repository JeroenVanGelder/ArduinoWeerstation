
#ifndef Weerstation_h
#define Weerstation_h
#include "Sensor.h"
#include "Time.h"
#include "Meting.h"

class Weerstation {
  public :
    Weerstation(char* name);
    Meting getMeting();
  private:
    char* _name;
};
#endif

