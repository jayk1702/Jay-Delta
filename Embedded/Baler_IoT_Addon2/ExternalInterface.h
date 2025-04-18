#include "HW_Config.h"

#define TARE_BTN_DEBOUNCE_TIME_MS           50
#define BALE_WRAP_STATUS_BZR_ON_TIME        3000 //3 seconds
#define MAX_OFFSET_VALUE_AT_ZERO_WEIGHT     99 //grams
#define MIN_OFFSET_VALUE_AT_ZERO_WEIGHT     -99  //grams

#define WEIGHT_ROUNDOFF_OFFSET_VALUE        99 //grms

#define POWER_UP_DELAY_HX711                100 //msec

#define MULTI_FUNC_BTN_LONG_PRESS_TIME      5000  //msec
#define MULTI_FUNC_STATUS_LED_INTERVAL      100 //msec

enum En_BaleWrapState
{
  BALE_WRAP_COUNT_REACHED=0,
  BALE_WRAP_BZR_HIGH=1,
  BALE_WRAP_BZR_LOW=2,
  UNDEFINED=255
};

void OnProximitySensEventDetect(void);
void ProxSnsrEvntHndlr(void);
void HndlBaleDataOnProxSnsrTmrExprd(void);
void UpdatePayloadDataAndTrnsmt(void);
void MultiFuncBtnConfig(void);
void MultiFuncBtnHndlr(void);
void BaleWrapStsBzrConfig(void);
void TurnOFFMultiFuncStatusLED(void);
void fetchStableWeightAndTrnsmtPayload(void);
void MultiFuncStsLEDConfig(void);
void OnMultiFuncBtnShortPress(void);
void OnMultiFuncBtnLongPress(void);
void DisplayMainMenu(void);
void SerialCommandsHandlr(void);
void MultiFuncLEDStateHndlr(void);
void WrapCountStsLEDandBzrHndlr(void);
void turnOffRelay(void);
void turnOnRelay(void);
void ConfigRpiPowerRelayPins(void);

void waitForUserCalibCmd(En_SerialCmd);

float Get_RoundOffWeight(float);
float Get_WeightKg(void);