/*
* `<Author>`         `<Time>`        `<Version>`  
*   xiaoyu          2016/03/04          1.0.0    
*/

#define MOS1_PIN 56
#define MOS2_PIN 57
extern unsigned char soft_pwm[2];
void setup() {
  pinMode(MOS1_PIN,OUTPUT);
  pinMode(MOS2_PIN,OUTPUT);
  soft_pwm[0] = 128;//  128/256*100% = 50%
  soft_pwm[1] = 51;//   51/256*100% = 20%
}
void loop() {

}

