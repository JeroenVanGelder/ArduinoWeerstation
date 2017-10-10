#ifndef Util_h 
#define Util_h 
#define WEATHERSTATION_ID  0 
 
class Util { 
  public : 
    Util(); 
    int getId(); 
    void registerWeatherstation(); 
    void ensureId(); 
    int* getIp(); 
    void getResponse2(); 
 
  private: 
    void writeId(); 
    void writeIp(int* myIp); 
 
}; 
#endif 