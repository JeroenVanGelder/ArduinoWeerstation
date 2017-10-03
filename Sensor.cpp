#include "Sensor.h"

unsigned int readTempValueRAW(int pin) {
  if (pin != -1)
    return analogRead(pin);
  return analogRead(thermistorPin);
}

float thermistorValue(int pin) {
  return ( 1024.0 * RESISTOR / (float)readTempValueRAW(pin) ) - RESISTOR ; //voltage divider Rtherm = ((Ui/Uo)*R)-R
}

float readTempValue(int pin) {
  // using the Steinhart-Hart equation http://en.wikipedia.org/wiki/Thermistor
  // 1/T= a + b*ln(R/Rt) + c*ln(R/Rt)^2 + d*ln(R/Rt)^3
  float logR; float temp;
  logR = log(thermistorValue(pin) / THERMISTOR);
  temp = 1 / (SHa + (SHb * logR) + (SHc * logR * logR) + (SHd * logR * logR * logR)); //Temperature in Kelvin
  temp = temp - 273.15; // Convert Kelvin to Celsius
  return temp;
}

float readLightDepedentResistor(int pin) {
  if (pin != -1)
    return analogRead(pin);
  return analogRead(LDRsensor);
}
