/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class PiStepper
 * \brief   Driver for Me Stepper device.
 * @file    PiStepper.cpp
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Driver for Stepper device.
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2016, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Description
 * This file is a drive for Me Stepper device.
 *
 * \par Method List:
 *
 *    1. void PiStepper::setMicroStep(int8_t value);
 *    2. void PiStepper::setpin(int slot);
 *    3. void PiStepper::moveTo(long absolute); 
 *    4. void PiStepper::move(long relative);
 *    5. boolean PiStepper::run();
 *    6. boolean PiStepper::runSpeed();
 *    7. void PiStepper::setMaxSpeed(float speed);
 *    8. void PiStepper::setAcceleration(float acceleration);
 *    9. void PiStepper::setSpeed(float speed);
 *    10. float PiStepper::speed();
 *    11. long PiStepper::distanceToGo();
 *    12. long PiStepper::targetPosition();
 *    13. long PiStepper::currentPosition();  
 *    14. void PiStepper::setCurrentPosition(long position);  
 *    15. void PiStepper::runToPosition();
 *    16. boolean PiStepper::runSpeedToPosition();
 *    17. void PiStepper::runToNewPosition(long position);
 *    18. void PiStepper::disableOutputs();
 *    19. void PiStepper::enableOutputs();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan        2016/03/05     1.0.0            Bulid the new
 * </pre>
 */

#include "PiStepper.h"

const zeropi_slot_type zeropi_slots[NUM_SLOTS] =
{
  {44, 45, 46, 47, 4, 3},
  {48, 49, 50, 51, 6, 5},
  {52, 53, 54, 55, 12, 10},
  {11, 7, 2, 38, 8, 9}
};

typedef enum
{
  DIRECTION_CCW = 0,  ///< Clockwise
  DIRECTION_CW  = 1   ///< Counter-Clockwise
} Direction;

/**
 * Alternate Constructor which can call your own function to map the stepper to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
PiStepper::PiStepper()
{

}

/**
 * Alternate Constructor which can call your own function to map the stepper to arduino port.
 * \param[in]
 *    slot - The slot of zeropi boards.
 */
PiStepper::PiStepper(int slot)
{
  _currentPos = 0;
  _targetPos = 0;
  _acceleration = 0;
  _lastStepTime = micros();
  _speed = 0;
  _dir = DIRECTION_CW;
  setCurrentPosition(0);
  _enable_pin = zeropi_slots[slot-1].pin[0];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[1];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[2];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[3];
  _step_data = zeropi_slots[slot-1].pin[4];
  _dir_data = zeropi_slots[slot-1].pin[5];
  pinMode(_dir_data, OUTPUT);
  pinMode(_step_data, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
}

/**
 * \par Function
 *    setMicroStep
 * \par Description
 *    Set the micro step.
 * \param[in]
 *    value - the Subdivided value.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::setMicroStep(int8_t value)
{
  _micro_step = value;
  switch (value)
  {
    case 1:
      digitalWrite(_micro_step_pin1,0);
      digitalWrite(_micro_step_pin2,0);
      digitalWrite(_micro_step_pin3,0);
      break;
    case 2:
      digitalWrite(_micro_step_pin1,1);
      digitalWrite(_micro_step_pin2,0);
      digitalWrite(_micro_step_pin3,0);
      break;
    case 4:
      digitalWrite(_micro_step_pin1,0);
      digitalWrite(_micro_step_pin2,1);
      digitalWrite(_micro_step_pin3,0);
      break;
    case 8:
      digitalWrite(_micro_step_pin1,1);
      digitalWrite(_micro_step_pin2,1);
      digitalWrite(_micro_step_pin3,0);
      break;
    case 16:
      digitalWrite(_micro_step_pin1,0);
      digitalWrite(_micro_step_pin2,0);
      digitalWrite(_micro_step_pin3,1);
      break;
    case 32:
      digitalWrite(_micro_step_pin1,1);
      digitalWrite(_micro_step_pin2,1);
      digitalWrite(_micro_step_pin3,1);
      break;
    default:
      digitalWrite(_micro_step_pin1,0);
      digitalWrite(_micro_step_pin2,0);
      digitalWrite(_micro_step_pin3,0);
      break;
  }
}

/**
 * \par Function
 *    setpin
 * \par Description
 *    Set pin for Stepper.
 * \param[in]
 *    slot - The slot of zeropi boards.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::setpin(int slot)
{
  _currentPos = 0;
  _targetPos = 0;
  _acceleration = 0;
  _lastStepTime = micros();
  _speed = 0;
  _dir = DIRECTION_CW;
  setCurrentPosition(0);
  _enable_pin = zeropi_slots[slot-1].pin[0];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[1];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[2];
  _micro_step_pin1 = zeropi_slots[slot-1].pin[3];
  _step_data = zeropi_slots[slot-1].pin[4];
  _dir_data = zeropi_slots[slot-1].pin[5];
  pinMode(_dir_data, OUTPUT);
  pinMode(_step_data, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
  pinMode(_micro_step_pin1, OUTPUT);
}

/**
 * \par Function
 *    moveTo
 * \par Description
 *    Stepper moves to the aim.
 * \param[in]
 *    absolute - The absolute length to Stepper's movement.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::moveTo(long absolute)
{
  if (_targetPos != absolute)
  {
    _targetPos = absolute;
    computeNewSpeed();
  }
}

/**
 * \par Function
 *    move
 * \par Description
 *    Stepper moves to the aim.
 * \param[in]
 *    relative - The relative length to Stepper's movement.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::move(long relative)
{
  moveTo(_currentPos + relative);
}

/**
 * \par Function
 *    runSpeed
 * \par Description
 *    The speed of Stepper's running.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return true or false.
 * \par Others
 *    None
 */
boolean PiStepper::runSpeed()
{
  // Dont do anything unless we actually have a step interval
  if (!_stepInterval)
  {
    return false;
  }

  if (micros() - _lastStepTime > _stepInterval)
  {
    if (_dir == DIRECTION_CW)
    {
      // Clockwise
      _currentPos += 1;
    }
    else
    {
      // Anticlockwise  
      _currentPos -= 1;
    }
    step();
    _lastStepTime = micros();
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * \par Function
 *    distanceToGo
 * \par Description
 *    The distance that Stepper should go.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the length of Stepper's running.
 * \par Others
 *    None
 */
long PiStepper::distanceToGo()
{
  return _targetPos - _currentPos;
}

/**
 * \par Function
 *    targetPosition
 * \par Description
 *    Stepper goes to target position.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the position of Stepper.
 * \par Others
 *    None
 */
long PiStepper::targetPosition()
{
  return _targetPos;
}

/**
 * \par Function
 *    currentPosition
 * \par Description
 *    Stepper's current position.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the current position of Stepper.
 * \par Others
 *    None
 */
long PiStepper::currentPosition()
{
  return _currentPos;
}

/**
 * \par Function
 *    setCurrentPosition
 * \par Description
 *    Set Stepper's current position.
 * \param[in]
 *    position - The current position for Stepper.
 * \par Output
 *    None
 * \par Return
 *    Return the current position of Stepper.
 * \par Others
 *    None
 */
void PiStepper::setCurrentPosition(long position)
{
  _targetPos = _currentPos = position;
  _n = 0;
  _stepInterval = 0;
}

/**
 * \par Function
 *    computeNewSpeed
 * \par Description
 *    Compute New Speed of Stepper.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::computeNewSpeed()
{
  long distanceTo = distanceToGo();
  long stepsToStop = (long)((_speed * _speed) / (2.0 * _acceleration));
  if (distanceTo == 0 && stepsToStop <= 1)
  {
    // We are at the target and its time to stop
    _stepInterval = 0;
    _speed = 0.0;
    _n = 0;
    return;
  }

  if (distanceTo > 0)
  {
    // We are anticlockwise from the target
    // Need to go clockwise from here, maybe decelerate now
    if (_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= distanceTo) || _dir == DIRECTION_CCW)
      {
        _n = -stepsToStop; // Start deceleration
      }
    }
    else if (_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < distanceTo) && _dir == DIRECTION_CW)
      {
        _n = -_n; // Start accceleration
      }
    }
  }
  else if (distanceTo < 0)
  {
    // We are clockwise from the target
    // Need to go anticlockwise from here, maybe decelerate
    if (_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= -distanceTo) || _dir == DIRECTION_CW)
      {
        _n = -stepsToStop; // Start deceleration
      }
    }
    else if (_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < -distanceTo) && _dir == DIRECTION_CCW)
      {
        _n = -_n; // Start accceleration
      }
    }
  }

  // Need to accelerate or decelerate
  if (_n == 0)
  {
    // First step from stopped
    _cn = _c0;
    _dir = (distanceTo > 0) ? DIRECTION_CW : DIRECTION_CCW;
  }
  else
  {
    // Subsequent step. Works for accel (n is +_ve) and decel (n is -ve).
    _cn = _cn - ((2.0 * _cn) / ((4.0 * _n) + 1)); // Equation 13
    _cn = max(_cn, _cmin);
  }
  _n++;
  _stepInterval = _cn;
  _speed = 1000000.0 / _cn;
  if (_dir == DIRECTION_CCW)
  {
    _speed = -_speed;
  }
}

/**
 * \par Function
 *    run
 * \par Description
 *    Stepper's status----run or not.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the status.
 * \par Others
 *    None
 */
boolean PiStepper::run()
{
  if((_speed == 0.0) || (distanceToGo() == 0))
  {
    return false;
  }

  if (runSpeed())
  {
	computeNewSpeed();
    return true;
  }
}

/**
 * \par Function
 *    setMaxSpeed
 * \par Description
 *    Set Max Speed for Stepper.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::setMaxSpeed(float speed)
{
  if (_maxSpeed != speed)
  {
    _maxSpeed = speed;
    _cmin = 1000000.0 / speed;
    // Recompute _n from current speed and adjust speed if accelerating or cruising
    if (_n > 0)
    {
      _n = (long)((_speed * _speed) / (2.0 * _acceleration)); // Equation 16
      computeNewSpeed();
    }
  }
}

/**
 * \par Function
 *    setAcceleration
 * \par Description
 *    Set Acceleration for Stepper.
 * \param[in]
 *    acceleration - The acceleration for Stepper.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::setAcceleration(float acceleration)
{
  if(acceleration == 0.0)
  {
    return;
  }
  if(_acceleration != acceleration)
  {
    _n = _n * (_acceleration / acceleration);
    //	_c0 = sqrt(2.0 / acceleration) * 1000000.0;
    // Accelerates at half the expected rate. Why?
    _c0 = sqrt(1.0/acceleration) * 1000000.0;
    _acceleration = acceleration;
    computeNewSpeed();
  }
}

/**
 * \par Function
 *    setSpeed
 * \par Description
 *    Set Speed for Stepper.
 * \param[in]
 *    speed - The speed of Stepper.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::setSpeed(float speed)
{
  if (speed == _speed)
  {
    return;
  }
  speed = constrain(speed, -_maxSpeed, _maxSpeed);
  if (speed == 0.0)
  {
    _stepInterval = 0;
  }

  else
  {
    _stepInterval = fabs(1000000.0 /speed);
    _dir = (speed > 0.0) ? DIRECTION_CW : DIRECTION_CCW;
  }
  _speed = speed;
}

/**
 * \par Function
 *    speed
 * \par Description
 *    The Speed of Stepper.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the Stepper's speed.
 * \par Others
 *    None
 */
float PiStepper::speed()
{
  return _speed;
}

/**
 * \par Function
 *    step
 * \par Description
 *    Stepper runs step by step.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::step()
{
  if(_dir == DIRECTION_CW)
  {
    digitalWrite(_dir_data,LOW);
  }
  else
  {
    digitalWrite(_dir_data,HIGH);
  }
  digitalWrite(_step_data, HIGH);
  delayMicroseconds(1);
  digitalWrite(_step_data, LOW);
}

/**
 * \par Function
 *    runToPosition
 * \par Description
 *    Stepper runs to position.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::runToPosition()
{
  while (run())
  {
    ;
  }
}

/**
 * \par Function
 *    runSpeedToPosition
 * \par Description
 *    The speed of Stepper on the way to position.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return true or false.
 * \par Others
 *    None
 */
boolean PiStepper::runSpeedToPosition()
{
  if (_targetPos == _currentPos)
  {
    return false;
  }
  if (_targetPos >_currentPos)
  {
	_dir = DIRECTION_CW;
  }
  else
  {
	_dir = DIRECTION_CCW;
  }
  return runSpeed();
}

/**
 * \par Function
 *    runToNewPosition
 * \par Description
 *    The Stepper runs to new position.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::runToNewPosition(long position)
{
  moveTo(position);
  runToPosition();
}

/**
 * \par Function
 *    disableOutputs
 * \par Description
 *    The Stepper disable the outputs.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::disableOutputs()
{
  digitalWrite(_enable_pin,1);
}

/**
 * \par Function
 *    enableOutputs
 * \par Description
 *    The Stepper disable the outputs.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void PiStepper::enableOutputs()
{
  digitalWrite(_enable_pin,0);
}
