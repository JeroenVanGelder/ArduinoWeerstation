#ifndef Util_h 
#define Util_h 
#define WEATHERSTATION_ID  0 
 
class Util { 
  public : 
    Util(); 
   
    int getId(); 
    int* getIp(); 
 
//  private: 
    void writeId(int id); 
    void writeIp(char* myIp); 
 
}; 
#endif 
