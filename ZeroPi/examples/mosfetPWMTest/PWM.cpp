#include "arduino.h"

#define MOS1_PIN 56
#define MOS2_PIN 57
unsigned char soft_pwm[2];
extern "C" {  
int sysTickHook(void)
  {
    static unsigned char pwm_count = 0;
    static unsigned char soft_pwm_0;
    static unsigned char soft_pwm_1;
    if (pwm_count == 0)
    {
      soft_pwm_0 = soft_pwm[0] >> 1; //0~127
      if (soft_pwm_0 > 0) digitalWrite(MOS1_PIN, 1); else digitalWrite(MOS1_PIN, 0);
      soft_pwm_1 = soft_pwm[1] >> 1; //0~127
      if (soft_pwm_1 > 0) digitalWrite(MOS2_PIN, 1); else digitalWrite(MOS2_PIN, 0);
    }
    if (soft_pwm_0 < pwm_count) digitalWrite(MOS1_PIN, 0);
    if (soft_pwm_1 < pwm_count) digitalWrite(MOS2_PIN, 0);
    pwm_count ++;
    pwm_count &= 0x7f;
    return 0;
  }
}
