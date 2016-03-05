/*class ZeroPiStepper
  {
  public:
  ZeroPiStepper(SLOT_NUM_t slot);
  void microstep(int value, DRIVER_t = DRV8825);//set Resolution
  void setDirection(int dir);
  void step(void);
  void enable(void);
  void disable(void);
  private:
  SLOT_NUM_t slot_num;
  };

  2-Phase Stepper Motor
  Steps per Revolution: 200
  Step Angle: 1.8°
  Test Voltage: 12V


  ZeroPi           Stepper Motor
    B+    <---->     black
    B-    <---->     green
    A-    <---->     red
    A+    <---->     blue
*/
/*
* `<Author>`         `<Time>`        `<Version>`  
*   xiaoyu          2016/03/04          1.0.0    
*/
#include "ZeroPi.h"
ZeroPiStepper step1(SLOT1);
ZeroPiStepper step2(SLOT2);
ZeroPiStepper step3(SLOT3);
ZeroPiStepper step4(SLOT4);



int i;
void setup() {
  //set 16 microstep   200*16=3200 pulses/circle
  step1.microstep(16);//default type = DRV8825   microstep(16,DRV8825)
  step2.microstep(16);
  step3.microstep(16);
  step4.microstep(16);

  step1.enable();
  step2.enable();
  step3.enable();
  step4.enable();
}

void loop() {
  //Stepper motor clockwise in a circle
  step1.setDirection(1);
  step2.setDirection(1);
  step3.setDirection(1);
  step4.setDirection(1);
  for (i = 0; i < 3200; i++)
  {
    step1.step();
    step2.step();
    step3.step();
    step4.step();
    delayMicroseconds(200);
  }
  delay(1000);
  
  //Stepper motor counter-clockwise revolution
  step1.setDirection(0);
  step2.setDirection(0);
  step3.setDirection(0);
  step4.setDirection(0);
  for (i = 0; i < 3200; i++)
  {
    step1.step();
    step2.step();
    step3.step();
    step4.step();
    delayMicroseconds(200);
  }
  delay(1000);
}

