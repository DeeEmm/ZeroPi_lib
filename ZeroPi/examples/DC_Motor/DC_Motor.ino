/*
class ZeroPiDCMotor
{
public:
  ZeroPiDCMotor(SLOT_NUM_t slot, CHANNEL_t channel);
  void run(int pwm);
  void stop(void);
  //    void brake(void);
private:
  SLOT_NUM_t slot_num;
  CHANNEL_t motor_channel;
};

*  Warning: Input Voltage < 13.5V
* `<Author>`         `<Time>`        `<Version>`  
*   xiaoyu          2016/03/04          1.0.0          
*/

#include "ZeroPi.h"

ZeroPiDCMotor motor1(SLOT1, CH_A);//A+ A-
ZeroPiDCMotor motor2(SLOT1, CH_B);//B+ B-

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.run(100);
  motor2.run(100);
  delay(1000);
  motor1.stop();
  motor2.stop();
  delay(1000);
  motor1.run(-100);
  motor2.run(-100);
  delay(1000);
  motor1.run(0);//as stop
  motor2.run(0);//as stop
  delay(1000);
}
