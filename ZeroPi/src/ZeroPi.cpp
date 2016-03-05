#include "Arduino.h"
#include "ZeroPi.h"

const SLOT_t slots[NUM_SLOTS] =
{
  {44, 45, 46, 47, 4, 3},
  {48, 49, 50, 51, 6, 5},
  {52, 53, 54, 55, 12, 10},
  {11, 7, 2, 38, 8, 9}
};

ZeroPiDCMotor::ZeroPiDCMotor(SLOT_NUM_t slot, CHANNEL_t channel)
{
  slot_num = slot;
  motor_channel = channel;
  for (int n = 0; n < SLOT_NUM_PINS; n++)
  {
    SET_OUTPUT(slots[slot_num].pin[n]);
  }
}

static void syncTC_8(Tc *TCx)
{
  while (TCx->COUNT8.STATUS.bit.SYNCBUSY);
}
void ZeroPiDCMotor::run(int pwm)
{
  pwm = constrain(pwm, -255, 255);
  switch (motor_channel)
  {
    case CH_A:
      if (pwm > 0)
      {
        WRITE(slots[slot_num].pin[MOTOR_AIN1], 1);
        WRITE(slots[slot_num].pin[MOTOR_AIN2], 0);
      }
      else
      {
        WRITE(slots[slot_num].pin[MOTOR_AIN1], 0);
        WRITE(slots[slot_num].pin[MOTOR_AIN2], 1);
      }
      pwm = abs(pwm);
      analogWrite(slots[slot_num].pin[MOTOR_PWMA], pwm);

      break;
    case CH_B:
      if (pwm > 0)
      {
        WRITE(slots[slot_num].pin[MOTOR_BIN1], 1);
        WRITE(slots[slot_num].pin[MOTOR_BIN2], 0);
      }
      else
      {
        WRITE(slots[slot_num].pin[MOTOR_BIN1], 0);
        WRITE(slots[slot_num].pin[MOTOR_BIN2], 1);
      }
      pwm = abs(pwm);
      analogWrite(slots[slot_num].pin[MOTOR_PWMB], pwm);
      break;
  }
}
/*
void ZeroPiDCMotor::stop(void)
{
  switch (motor_channel)
  {
    case CH_A:
      WRITE(slots[slot_num].pin[MOTOR_AIN1], 0);
      WRITE(slots[slot_num].pin[MOTOR_AIN2], 0);
      break;
    case CH_B:
      WRITE(slots[slot_num].pin[MOTOR_BIN1], 0);
      WRITE(slots[slot_num].pin[MOTOR_BIN2], 0);
      break;
  }
}
*/
void ZeroPiDCMotor::stop(void)
{
  switch (motor_channel)
  {
    case CH_A:
      WRITE(slots[slot_num].pin[MOTOR_AIN1], 1);
      WRITE(slots[slot_num].pin[MOTOR_AIN2], 1);
      break;
    case CH_B:
      WRITE(slots[slot_num].pin[MOTOR_BIN1], 1);
      WRITE(slots[slot_num].pin[MOTOR_BIN2], 1);
      break;
  }
}

ZeroPiStepper::ZeroPiStepper(SLOT_NUM_t slot)
{
  slot_num = slot;
  for (int n = 0; n < SLOT_NUM_PINS; n++)
  {
    SET_OUTPUT(slots[slot_num].pin[n]);
  }
  disable();
}

void ZeroPiStepper::microstep(int value, DRIVER_t type)
{
  switch (type)
  {
    case A4982://only MS1 MS2
      switch (value)
      {
        case 1:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          break;
        case 2:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          break;
        case 4:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          break;
        case 16:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          break;
        default:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          break;
      }
      break;
    case A4988:
      switch (value)
      {
        case 1:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 2:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 4:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 8:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 16:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        default:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
      }
      break;
    case DRV8825:
      switch (value)
      {
        case 1:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 2:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 4:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 8:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 16:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        case 32:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        default:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
      }
      break;
    case TB67S269:
    case TB67S109:
      switch (value)
      {
        case 1:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        case 2://Half step resolution(Type (A))
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 4:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        case 8:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        case 16:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 0);
          break;
        case 32:
          WRITE(slots[slot_num].pin[STEP_MS1], 1);
          WRITE(slots[slot_num].pin[STEP_MS2], 1);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
        default:
          WRITE(slots[slot_num].pin[STEP_MS1], 0);
          WRITE(slots[slot_num].pin[STEP_MS2], 0);
          WRITE(slots[slot_num].pin[STEP_MS3], 1);
          break;
      }
      break;
    default:
      break;
  }
}
void ZeroPiStepper::setDirection(int dir)
{
  WRITE(slots[slot_num].pin[STEP_DIR], dir);
}
void ZeroPiStepper::step(void)
{
  WRITE(slots[slot_num].pin[STEP_STP], HIGH);
  __NOP();
  WRITE(slots[slot_num].pin[STEP_STP], LOW);
}
void ZeroPiStepper::enable(void)
{
  WRITE(slots[slot_num].pin[STEP_EN], 0);
}
void ZeroPiStepper::disable(void)
{
  WRITE(slots[slot_num].pin[STEP_EN], 1);
}