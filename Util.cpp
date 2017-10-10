#include "Util.h" 
#include "HttpRequest.h" 
#include <EEPROM.h> 
#include <Ethernet2.h> 
 
EthernetClient client2; 
IPAddress server2(10, 42, 0, 1); // IP2 of webserver 
Util::Util(){}  
void Util::getResponse2() { 
 
  while (!client2.available()) { 
    delay(5); // let's take five. Here we should check for time out 
    Serial.print("."); 
  } 
  Serial.println("Response received:"); 
  while (client2.available()) { 
    char c = client2.read(); 
    Serial.print(c); 
    delay(1); // give input some time do to it's thingpie. 
  } 
  Serial.println(); 
  Serial.println("Response read, now we can disconnect."); 
  if (!client2.connected()) { 
    Serial.println("disconnecting..."); 
    client2.stop(); 
  } 
  Serial.println("We are disconnected"); 
} 
 
int Util::getId() { 
  int ID = EEPROM.read(0); 
  if (ID > 0 and ID < 256) 
    return ID; 
 
  return 0; 
} 
 
void Util::writeIp(int* myIp) { 
  EEPROM.write(1, myIp[0]); 
  EEPROM.write(2, myIp[1]); 
  EEPROM.write(3, myIp[2]); 
  EEPROM.write(4, myIp[3]); 
} 
 
void Util::registerWeatherstation() { 
  char* ipServer = "10.42.0.1"; 
 
  HttpRequest httpRequestPost("POST ", "http://10.42.0.1/arne/SignIn", "HTTP/1.1 "); 
  char* loginMessage = "{\"id\":0}"; 
 
char* sizeje =(sizeof(loginMessage)/sizeof(char)); 
Serial.println(sizeje); 
  httpRequestPost.addRequestHeader("Host: ", ipServer); 
  httpRequestPost.addRequestHeader("Connection: ", "close"); 
  httpRequestPost.addRequestHeader("Content-Type: ", "application/json"); 
  httpRequestPost.addRequestHeader("Content-Length: ", 8); 
  httpRequestPost.parseSigninToJsonBody(loginMessage); 
 
  if (client2.connect(server2, 80)) { 
   
    Serial.println("Connected to webserver"); 
    httpRequestPost.sendRequest(client2); 
    getResponse2(); 
  } 
  else { 
    Serial.println("Connection failed"); 
  } 
 
  //@todo  stuur bericht naar gateway met id registreer ip daarna 
 
  //int newIp[4] = {1, 1, 1, 1}; 
  //  writeIp(newIp); 
} 
 
void Util::writeId() { 
  EEPROM.write(0, WEATHERSTATION_ID); 
} 
void Util::ensureId() { 
  if (!(getId() > 0 and getId() < 256)) 
    writeId(); 
} 