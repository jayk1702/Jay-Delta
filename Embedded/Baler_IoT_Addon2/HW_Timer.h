#include "HW_Config.h"

#define TIMER_FREQ (1000000) //1MHz
//TODO:Need to get minimum time to complete a single wrap. Assuming 5sec 
#define PROX_SNSR_TMR_ALARM_VALUE (5000000) //5 sec in uSec
#define AUTO_RELOAD false
#define RELOAD_COUNT 0

void IRAM_ATTR timerInterrupt(void);
void HwTimerIntrptConfig(void);
void RestartTimer(En_MachineEvent);
void StartTimer(En_MachineEvent);
void StopTimer(En_MachineEvent);
void HasTimerExpired(void);
void ResetTimerValue(En_MachineEvent);