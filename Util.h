#include <string.h>
#include "Meting.h"
#include <ArduinoJson.h>

#ifndef Util_h 
#define Util_h 
#define WEATHERSTATION_ID  0 
 
class Util { 
  public : 
    Util(); 
   
    int getId(); 
    int* getIp();
    char* getIpCharArray();
    void parseGetIdJson(String json);
    char* parseMetingToJsonBody(Meting inputMeting);
    char* parseSignInToJsonBody(int getal);
    
//  private: 
    void writeId(int id); 
    void writeIp(char* myIp);

  private:
  
}; 
#endif 
