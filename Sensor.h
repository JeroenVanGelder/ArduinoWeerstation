#ifndef sensor_h
#define sensor_h
#include <SPI.h>

const int thermistorPin = A0;
const int LDRsensor = A1; 
const int calibratieTemperatuur = 15;

#define RESISTOR 10000 //voltage divider resistor
#define THERMISTOR 4700 //thermistor value at 25 degrees
//Steinhart-Hart parameter a, b, c and d (from datasheet, NTC 4.7kohm)
#define SHa 0.003354016
#define SHb 0.0002569850
#define SHc 0.000002620131
#define SHd 0.00000006383091

unsigned int readTempValueRAW(int pin);

float thermistorValue(int pin);

float readTempValue(int pin);

float readLightDepedentResistor(int pin);

#endif
