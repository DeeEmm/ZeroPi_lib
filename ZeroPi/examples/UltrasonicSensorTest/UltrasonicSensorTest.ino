/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    UltrasonicSensorTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Description: this file is sample code for Me ultrasonic sensor module.
 *
 * Function List:
 * 1. double MeUltrasonicSensor::distanceCm(uint16_t MAXcm)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2016/03/05    1.0.0          Builed the new
 * </pre>
 */
#include "UltrasonicSensor.h"

UltrasonicSensor ultraSensor(A1); /* Ultrasonic data pin connected to arduino port A1 */

void setup()
{
  SerialUSB.begin(9600);
}

void loop()
{
  SerialUSB.print("Distance : ");
  SerialUSB.print(ultraSensor.distanceCm() );
  SerialUSB.println(" cm");
  delay(100); /* the minimal measure interval is 100 milliseconds */
}

