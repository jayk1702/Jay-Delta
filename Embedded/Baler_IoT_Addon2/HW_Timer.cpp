#include "HW_Timer.h"

hw_timer_t *HrzWrapEvent_timer = NULL;

volatile bool hasTimerExpired = false;
volatile bool IsTimerStopped = false;
//bool timerRunning = false;

typedef struct
{
  hw_timer_t *timer;
  En_MachineEvent interruptType;
}TimerIntrpConfig_T;

TimerIntrpConfig_T TimerIntrptCfg[] = {{HrzWrapEvent_timer, EN_MACHINE_EVNT_PROXIMITY_SNSR}};

En_MachineEvent RcvdTimerIntrptType = EN_MACHINE_EVNT_UNDEFINED;

void IRAM_ATTR timerInterrupt(void *arg) 
{
  hasTimerExpired = true;
  if(arg != NULL)
  {
    RcvdTimerIntrptType = *(En_MachineEvent*)arg;
  }
}

void HwTimerIntrptConfig(void)
{
  unsigned char TmrIntrptIdx;

  for(TmrIntrptIdx = NUM_ZERO; TmrIntrptIdx < sizeof(TimerIntrptCfg)/sizeof(TimerIntrptCfg[NUM_ZERO]); TmrIntrptIdx++)
  {
#if ENABLE_DEBUG
    Serial.print("[INFO]TmrIntrptIdx:");
    Serial.println(TmrIntrptIdx);
#endif
    TimerIntrptCfg[TmrIntrptIdx].timer = timerBegin(TIMER_FREQ);
    timerAttachInterruptArg(TimerIntrptCfg[TmrIntrptIdx].timer, &timerInterrupt,&(TimerIntrptCfg[TmrIntrptIdx].interruptType));
    timerAlarm(TimerIntrptCfg[TmrIntrptIdx].timer, PROX_SNSR_TMR_ALARM_VALUE, AUTO_RELOAD, RELOAD_COUNT);
    //Should Stop timer alarm manually before it expires itself
    //to re-start timer alarm manually when proxSnsr intrpt triggered
    timerStop(TimerIntrptCfg[TmrIntrptIdx].timer);
    //Making flag to true to let know the time has stopped 
    IsTimerStopped = true;
#if ENABLE_DEBUG
    Serial.println("[INFO]Stop timer alarm initially!");
#endif
  }
}

void HasTimerExpired(void)
{
  if(hasTimerExpired == true)
  {
    // Tasks to perform when the Timer interrupt is activated
    if(RcvdTimerIntrptType == EN_MACHINE_EVNT_PROXIMITY_SNSR)
    {
      StopTimer(EN_MACHINE_EVNT_PROXIMITY_SNSR);
      HndlBaleDataOnProxSnsrTmrExprd();
    }
    else
    {
      //
    }
    
    hasTimerExpired = false;
  }
}

void StartTimer(En_MachineEvent TimerEvntType)
{
  switch(TimerEvntType)
  {
    case EN_MACHINE_EVNT_PROXIMITY_SNSR:
      // Start the timer
      timerStart(TimerIntrptCfg[EN_MACHINE_EVNT_PROXIMITY_SNSR].timer);  // Start the timer
#if ENABLE_DEBUG
      Serial.println("[INFO]ProxSensorEvent Timer started!");
#endif
      break;

    default:
#if ENABLE_DEBUG
      Serial.print("[INFO]Invalid");
#endif
      break;
  }
}

void RestartTimer(En_MachineEvent TimerEvntType)
{
  switch(TimerEvntType)
  {
    case EN_MACHINE_EVNT_PROXIMITY_SNSR:
      // Restart the timer if it is not already running
      timerRestart(TimerIntrptCfg[EN_MACHINE_EVNT_PROXIMITY_SNSR].timer);  // Start the timer
#if ENABLE_DEBUG
      Serial.println("[INFO]ProxSensorEvent Timer Restarted!");
#endif
      break;

    default:
#if ENABLE_DEBUG
      Serial.print("[INFO]Invalid");
#endif
      break;
  }
}

void StopTimer(En_MachineEvent TimerEvntType)
{
  switch(TimerEvntType)
  {
    case EN_MACHINE_EVNT_PROXIMITY_SNSR:
      // Stop the timer
      timerStop(TimerIntrptCfg[EN_MACHINE_EVNT_PROXIMITY_SNSR].timer);
      IsTimerStopped = true;
#if ENABLE_DEBUG
      Serial.println("[INFO]ProxSensorEvent Timer stopped!");
#endif
      break;

    default:
#if ENABLE_DEBUG
      Serial.print("[INFO]Invalid");
#endif
      break;
  }
}

void ResetTimerValue(En_MachineEvent TimerEvntType)
{
  switch(TimerEvntType)
  {
    case EN_MACHINE_EVNT_PROXIMITY_SNSR:
      // Timer value reset
      timerWrite(TimerIntrptCfg[EN_MACHINE_EVNT_PROXIMITY_SNSR].timer, NUM_ZERO);
#if ENABLE_DEBUG
      Serial.println("[INFO]ProxSensorEvent Timer value reset!");
#endif
      break;

    default:
#if ENABLE_DEBUG
      Serial.print("[INFO]Invalid");
#endif
      break;
  }
}