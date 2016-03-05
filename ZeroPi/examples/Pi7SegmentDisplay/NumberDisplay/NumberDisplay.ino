/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    NumberDisplay.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Description: this file is sample code for Seven-Segment Display device.
 *          It displays number from 0 to 100.
 * Function List:
 *    1. void    Pi7SegmentDisplay::display(int16_t value)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2016/03/05     1.0.0            Rebuild the new.
 * </pre>
 */
#include "Pi7SegmentDisplay.h"

Pi7SegmentDisplay disp(A1,A2);  //A1 data pin, A2 clk pin;

int16_t i = 0;
void setup()
{
}

void loop()
{
  if(i > 100)
  {
    i = 0;
  }
  disp.display(i++);
  delay(100);
}

