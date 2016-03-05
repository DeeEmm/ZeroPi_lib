#include "arduino.h"
#include "Temperature.h"
int current_temperature0_raw = 0 ;
float current_temperature0 = 0.0;
int current_temperature1_raw = 0;
float current_temperature1 = 0.0;
static volatile bool temp_meas_ready = false;
static void* heater_ttbl_map[2] = {(void*)HEATER_0_TEMPTABLE, (void*)HEATER_1_TEMPTABLE};
static uint8_t heater_ttbllen_map[2] = {HEATER_0_TEMPTABLE_LEN, HEATER_1_TEMPTABLE_LEN};

#define PGM_RD_W(x)   (short)pgm_read_word(&x)
// Derived from RepRap FiveD extruder::getTemperature()
// For hot end temperature measurement.
static float analog2temp(int raw, uint8_t e) {
  float celsius = 0;
  uint8_t i;
  short(*tt)[][2] = (short(*)[][2])(heater_ttbl_map[e]);

  for (i = 1; i < heater_ttbllen_map[e]; i++) {
    if (PGM_RD_W((*tt)[i][0]) > raw) {
      celsius = PGM_RD_W((*tt)[i - 1][1]) +
                (raw - PGM_RD_W((*tt)[i - 1][0])) *
                (float)(PGM_RD_W((*tt)[i][1]) - PGM_RD_W((*tt)[i - 1][1])) /
                (float)(PGM_RD_W((*tt)[i][0]) - PGM_RD_W((*tt)[i - 1][0]));
      break;
    }
  }

  // Overflow: Set to last value in the table
  if (i == heater_ttbllen_map[e]) celsius = PGM_RD_W((*tt)[i - 1][1]);

  return celsius;
}

float readTtemperature0()
{
  float temp = analog2temp(current_temperature0_raw, 0);
  return temp;
}

float readTtemperature1()
{
  return analog2temp(current_temperature1_raw, 1);
}

/**
   Stages in the ISR loop
*/
enum TempState {
  PrepareTemp_0,
  MeasureTemp_0,
  PrepareTemp_1,
  MeasureTemp_1,
  StartupDelay // Startup, delay initial temp reading a tiny bit so the hardware can settle
};

static unsigned long raw_temp0_value = 0;
static unsigned long raw_temp1_value = 0;

static void set_current_temp_raw() {
  current_temperature0_raw = raw_temp0_value;
  current_temperature1_raw = raw_temp1_value;
  temp_meas_ready = true;
}

//T0  PA05
//T1  PB02
// temperature sensor
void ZeroPiTemperatureInit(void)
{
  //  int portT0 = PORTA;
  //  int pinT0 = 5;
  //  int portT1 = PORTB;
  //  int pinT1 = 2
  uint32_t temp ;

  // Get whole current setup for both odd and even pins and remove odd one
  temp = (PORT->Group[PORTA].PMUX[5 >> 1].reg) & PORT_PMUX_PMUXE( 0xF ) ;
  // Set new muxing
  PORT->Group[PORTA].PMUX[5 >> 1].reg = temp | PORT_PMUX_PMUXO( PORT_PMUX_PMUXO_B_Val ) ;
  // Enable port mux
  PORT->Group[PORTA].PINCFG[5].reg |= PORT_PINCFG_PMUXEN ;

  temp = (PORT->Group[PORTB].PMUX[2 >> 1].reg) & PORT_PMUX_PMUXO( 0xF ) ;
  PORT->Group[PORTB].PMUX[2 >> 1].reg = temp | PORT_PMUX_PMUXE( PORT_PMUX_PMUXE_B_Val ) ;
  PORT->Group[PORTB].PINCFG[2].reg |= PORT_PINCFG_PMUXEN ; // Enable port mux

  ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_10BIT_Val;//10bit ADC
  while (ADC->STATUS.bit.SYNCBUSY == 1);
  ADC->CTRLA.bit.ENABLE = 0x01;
  while (ADC->STATUS.bit.SYNCBUSY == 1);
}

inline void TemperatureSampling()
{
  static unsigned char temp_count = 0;
  static TempState temp_state = StartupDelay;
  switch (temp_state) {
    case PrepareTemp_0:
      ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
      ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[A4].ulADCChannelNumber;
      ADC->SWTRIG.bit.START = 1;
      temp_state = MeasureTemp_0;
      break;
    case MeasureTemp_0:
      raw_temp0_value += ADC->RESULT.reg;
      temp_state = PrepareTemp_1;

      break;
    case PrepareTemp_1:
      ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
      ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[A5].ulADCChannelNumber;
      ADC->SWTRIG.bit.START = 1;
      temp_state = MeasureTemp_1;
      break;
    case MeasureTemp_1:
      raw_temp1_value += ADC->RESULT.reg;
      temp_state = PrepareTemp_0;
      temp_count++;
      break;

    case StartupDelay:
      ZeroPiTemperatureInit();
      temp_state = PrepareTemp_0;
      break;
  } // switch(temp_state)

  if (temp_count >= OVERSAMPLENR) { // 4 * 16 * 1  = 64ms.
    // Update the raw values if they've been read. Else we could be updating them during reading.
    //if (!temp_meas_ready)
    set_current_temp_raw();
    temp_count = 0;
    raw_temp0_value = 0;
    raw_temp1_value = 0;
  }
}
extern "C" {
  int sysTickHook(void)
  {
    TemperatureSampling();
    return 0;
  }
}
