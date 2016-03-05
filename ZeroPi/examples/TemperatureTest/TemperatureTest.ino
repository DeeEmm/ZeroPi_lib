/*

  Setting the thermistor type in the file Temperature.h
  As follows:
  #define TEMP_SENSOR_0 11 // 100k beta 3950 1% thermistor (4.7k pullup)
  #define TEMP_SENSOR_1 11 // 100k beta 3950 1% thermistor (4.7k pullup)

  `<Author>`         `<Time>`        `<Version>`
    xiaoyu          2016/03/04          1.0.0
*/

#include "Temperature.h"

void setup() {
}
void loop() {
  SerialUSB.print("T0="); SerialUSB.println(readTtemperature0()); //read T0 Ttemperature
  SerialUSB.print("T1="); SerialUSB.println(readTtemperature1()); ////read T0 Ttemperature
  SerialUSB.println();
  delay(1000);
}

