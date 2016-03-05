/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    TimeDisplay.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Description: this file is sample code for Seven-Segment LED device.
 *          It acts as a timer.
 * Function List:
 *    1. void Pi7SegmentDisplay::init(void)
 *    2. void Pi7SegmentDisplay::set(uint8_t = BRIGHT_2, uint8_t = ADDR_AUTO, \
                                        uint8_t = STARTADDR)
 *    3. void Pi7SegmentDisplay::display(uint8_t DispData[]);
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2016/03/05     1.0.0            Rebuild the new.
 * </pre>
 */

#include "Pi7SegmentDisplay.h"

uint8_t		TimeDisp[] = { 0x00, 0x00, 0x00, 0x00 };
unsigned char	second;
unsigned char	minute		= 0;
unsigned char	hour		= 12;
long		lastTime	= 0;

Pi7SegmentDisplay disp(A1,A2);  //A1 data pin, A2 clk pin;

void setup()
{
  disp.set();
  disp.init();
}

void loop()
{
  if(millis() - lastTime >= 1000)
  {
    TimingISR();

    TimeUpdate();
    disp.display(TimeDisp);

    lastTime = millis();
  }
}

void TimingISR()
{
  second++;
  if(second == 60)
  {
    minute++;
    if(minute == 60)
    {
      hour++;
      if(hour == 24)
      {
        hour = 0;
      }
      minute = 0;
    }
    second = 0;
  }
}

void TimeUpdate(void)
{
  TimeDisp[0] = minute / 10;
  TimeDisp[1] = minute % 10;
  TimeDisp[2] = second / 10;
  TimeDisp[3] = second % 10;
}

