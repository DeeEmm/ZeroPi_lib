/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   Pi7SegmentDisplay
 * \brief   Driver for Me 7-Segment Serial Display module.
 * @file    Pi7SegmentDisplay.h
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/05
 * @brief   Header file for Pi7SegmentDisplay.cpp.
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
 * Driver for Me 7-Segment Serial Display module.
 * \par Method List:
 *
 *    1.    void    Pi7SegmentDisplay::init(void);
 *    2.    void    Pi7SegmentDisplay::set(uint8_t brightness, uint8_t SetData, uint8_t SetAddr);
 *    3.    void    Pi7SegmentDisplay::setpin(uint8_t dataPin, uint8_t clkPin);
 *    4.    void    Pi7SegmentDisplay::write(uint8_t SegData[]);
 *    5.    void    Pi7SegmentDisplay::write(uint8_t BitAddr, uint8_t SegData);
 *    6.    void    Pi7SegmentDisplay::display(uint16_t value);
 *    7.    void    Pi7SegmentDisplay::display(int16_t value);
 *    8.    void    Pi7SegmentDisplay::display(int value);
 *    9.    void    Pi7SegmentDisplay::display(float value);
 *    10.   int16_t Pi7SegmentDisplay::checkNum(float v,int16_t b);
 *    11.   void    Pi7SegmentDisplay::display(double value, uint8_t digits);
 *    12.   void    Pi7SegmentDisplay::display(uint8_t BitAddr, uint8_t DispData,);
 *    14.   void    Pi7SegmentDisplay::display(uint8_t BitAddr, uint8_t DispData, uint8_t point_on);
 *    15.   void    Pi7SegmentDisplay::clearDisplay(void);
 *    16.   void    Pi7SegmentDisplay::setBrightness(uint8_t brightness);
 *    17.   void    Pi7SegmentDisplay::coding(uint8_t DispData[]);
 *    18.   uint8_t Pi7SegmentDisplay::coding(uint8_t DispData);
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2016/03/05    1.0.0            Rebuild the new.
 * </pre>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Pi7SegmentDisplay_H
#define Pi7SegmentDisplay_H

//************definitions for TM1637*********************
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>


/* Exported constants --------------------------------------------------------*/
/******************definitions for TM1637**********************/
const uint8_t   ADDR_AUTO = 0x40;   //Automatic address increment mode
const uint8_t   ADDR_FIXED = 0x44;   //Fixed address mode
const uint8_t   STARTADDR = 0xc0;   //start address of display register
const uint8_t   SEGDIS_ON = 0x88;   //diplay on
const uint8_t   SEGDIS_OFF = 0x80;   //diplay off
/**** definitions for the clock point of the digit tube *******/
const uint8_t POINT_ON = 1;
const uint8_t POINT_OFF = 0;
/**************definitions for brightness***********************/
const uint8_t BRIGHTNESS_0 = 0;
const uint8_t BRIGHTNESS_1 = 1;
const uint8_t BRIGHTNESS_2 = 2;
const uint8_t BRIGHTNESS_3 = 3;
const uint8_t BRIGHTNESS_4 = 4;
const uint8_t BRIGHTNESS_5 = 5;
const uint8_t BRIGHTNESS_6 = 6;
const uint8_t BRIGHTNESS_7 = 7;
///@brief Class for numeric display module

/**
 * Class: Pi7SegmentDisplay
 * \par Description
 * Declaration of Class Pi7SegmentDisplay.
 */
class Pi7SegmentDisplay
{
public:
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  Pi7SegmentDisplay(void);

/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port. 
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 */
  Pi7SegmentDisplay(uint8_t dataPin, uint8_t clkPin);

/**
 * \par Function
 *    init
 * \par Description
 *    Initialization the display, here just call function clearDisplay.
 * \par Output  
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void init(void); // Clear display
  
/**
 * \par Function
 *    set
 * \par Description
 *    Set brightness, data and address.
 * \param[in]
 *    brightness - Brightness, defined in Pi7SegmentDisplay.h from BRIGHTNESS_0 to BRIGHTNESS_7.
 * \param[in]
 *    SetData - First address for display data
 * \param[in]
 *    SetAddr - First address for display
 * \par Output
 *    Cmd_SetData - Private variable Cmd_SetData of class Pi7SegmentDisplay.
 *    Cmd_SetAddr - Private variable Cmd_SetAddr of class Pi7SegmentDisplay.
 *    Cmd_DispCtrl - Control command for Me 7 Segment Serial Display module.
 * \return
 *    None
 * \par Others
 *    None
 */
  void set(uint8_t = BRIGHTNESS_2, uint8_t = ADDR_AUTO, uint8_t = STARTADDR);// Take effect next display cycle.
  
/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset Seven-Segment LED module's data pin and its clock pin then clear display.
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    Set global variable _KeyPin and _clkPin
 */
  void setpin(uint8_t dataPin, uint8_t clkPin);

/**
 * \par Function
 *    write
 * \par Description
 *    White data array to certain address.
 * \param[in]
 *    SegData[] - Data array to write to module.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void write(uint8_t SegData[]);
  
/**
 * \par Function
 *    write
 * \par Description
 *    Write data to certain address.
 * \param[in]
 *    BitAddr - Bit address of data.
 * \param[in]
 *    SegData - Data to display.
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void write(uint8_t BitAddr, uint8_t SegData);
  
/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is uint16_t
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint16_t value);
  
/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is int16_t
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(int16_t value);
/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is int
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(int value);

/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is float
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(float value);

/**
 * \par Function
 *    checkNum
 * \par Description
 *    Extraction values to be displayed of float data
 * \param[in]
 *    v - Value to display.
 * \param[in]
 *    b - Value to display.
 * \par Output
 *    None
 * \return
 *    The data removal of the decimal point
 * \par Others
 *    None
 */
  int16_t checkNum(float v,int16_t b);

/**
 * \par Function
 *    display
 * \par Description
 *    Display double number.
 * \param[in]
 *    value - Value to display.
 * \param[in]
 *    digits - Number of digits to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(double value, uint8_t = 1);

/**
 * \par Function
 *    display
 * \par Description
 *    Display 8 bit number array.
 * \param[in]
 *    DispData[] - The data that needs to be displayed store in this array.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint8_t DispData[]);

/**
 * \par Function
 *    display
 * \par Description
 *    Display data to certain digit.
 * \param[in]
 *    BitAddr - Address to display.
 * \param[in]
 *    DispData - Data to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint8_t BitAddr, uint8_t DispData);

/**
 * \par Function
 *    display
 * \par Description
 *    Display data to certain digit.
 * \param[in]
 *    BitAddr - Address to display.
 * \param[in]
 *    DispData - Data to display.
 * \param[in]
 *    point_on - Display the point or not.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */ 
  void display(uint8_t BitAddr, uint8_t DispData, uint8_t point_on);

/**
 * \Function
 *    clearDisplay
 * \Description
 *    Clear display.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void clearDisplay(void);
  
/**
 * \par Function
 *    setBrightness
 * \par Description
 *    Set brightness.
 * \param[in]
 *    brightness - Brightness, defined in Pi7SegmentDisplay.h from BRIGHTNESS_0 to BRIGHTNESS_7.
 * \par Output
 *    Cmd_DispCtrl - Control command for Me 7 Segment Serial Display module.
 * \return
 *    None
 * \par Others
 *    None
 */
  void setBrightness(uint8_t brightness);
  
/**
 * \par Function
 *    coding
 * \par Description
 *    Set display data using look up table.
 * \param[in]
 *    DispData[] - DataArray to display.
 * \par Output
 *    DispData[] - DataArray be transcoded.
 * \return
 *    None
 * \par Others
 *    None
 */
  void coding(uint8_t DispData[]);

/**
 * \par Function
 *    coding
 * \par Description
 *    Return display data from look up table.
 * \param[in]
 *    DispData - Data need be transcoded.
 * \par Output
 *    None
 * \return
 *    Return the value of transcoding
 * \par Others
 *    None
 */
  uint8_t coding(uint8_t DispData);
private:
  uint8_t Cmd_SetData;
  uint8_t Cmd_SetAddr;
  uint8_t Cmd_DispCtrl;
  bool _PointFlag; //_PointFlag=1:the clock point on

/**
 * \par Function
 *    writeByte
 * \par Description
 *    Write one byte to TM1637.
 * \param[in]
 *    wr_data - Data to write to module.
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void writeByte(uint8_t wr_data);// Write 8 bits data to tm1637.
  
/**
 * \par Function
 *    start
 * \par Description
 *    Send start signal to TM1637
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void start(void);// Send start bits
  void point(bool PointFlag);// Whether to light the clock point ":". Take effect next display cycle.
 
/**
 * \par Function
 *    stop
 * \par Description
 *    Send the stop signal to TM1637.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void stop(void); // Send stop bits.
  uint8_t _clkPin;
  uint8_t _dataPin;
};
#endif
