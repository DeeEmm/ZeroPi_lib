/**
 * \par Copyright (C), 2012-2015, MakeBlock
 * @file    TestStepperDriver.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Description: this file is sample code for Stepper Driver device.
 * Our API is same as AccelStepper, and you can view the instructions on
 * http://www.airspayce.com/mikem/arduino/AccelStepper/
 *
 * Function List:
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2016/03/05    1.0.0          build the new.
 * </pre>
 */

#include "PiStepper.h"

PiStepper stepper(SLOT1);

void setup()
{
  SerialUSB.begin(9600);
  // Change these to suit your stepper if you want
  stepper.enableOutputs();
  stepper.setMicroStep(32);
  stepper.setMaxSpeed(3200);
  stepper.setAcceleration(20000);
  stepper.move(32000);
}

void loop()
{
  stepper.run();
}
