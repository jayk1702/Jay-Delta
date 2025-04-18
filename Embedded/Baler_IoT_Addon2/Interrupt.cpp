#include "Interrupt.h"

// Define an array of function pointers for callback functions
void (*callbackFunctions[])(void) = {
  ProxSnsrEvntCB,
  HrzWrapStartEventCB,
  UnloadingEventCB
};

extern MachineEvent_T MachineEvent;

void MachineEventPinsConfig(void)
{
  int IntrIdx=0;
  
  pinMode(PROX_SEN_EVENT_PIN, INPUT_PULLUP);
  
  //Configure interrupts w.r.t the machine type
  if(Get_MachineType() == EN_MACHINE_TYPE_ASB)
  {
    pinMode(HRZ_WRAP_START_EVENT_PIN, INPUT_PULLUP);
    pinMode(UNLOADING_EVENT_PIN, INPUT_PULLUP);
    // Define an array of InterruptConfig structures
    InterruptConfig_T MachEvntIntrpts[] = {
      {PROX_SEN_EVENT_PIN, EN_MACHINE_EVNT_PROXIMITY_SNSR, FALLING},
      {HRZ_WRAP_START_EVENT_PIN, EN_MACHINE_EVNT_HR_WRAP_STARTED, FALLING},
      {UNLOADING_EVENT_PIN, EN_MACHINE_EVNT_BALE_UNLOADING_DOWN, FALLING}
    };

    // Attach interrupts for each configuration
    for (IntrIdx = 0; IntrIdx < sizeof(MachEvntIntrpts)/sizeof(MachEvntIntrpts[NUM_ZERO]); IntrIdx++) 
    {
      attachInterruptFromConfig(MachEvntIntrpts[IntrIdx]);
    }
  }
  else if(Get_MachineType() == EN_MACHINE_TYPE_MSB)
  {
    // Define an array of InterruptConfig structures
    InterruptConfig_T MachEvntIntrpts[] = {
      {PROX_SEN_EVENT_PIN, EN_MACHINE_EVNT_PROXIMITY_SNSR, FALLING}
    };

    // Attach interrupts for each configuration
    for (IntrIdx = 0; IntrIdx < sizeof(MachEvntIntrpts)/sizeof(MachEvntIntrpts[NUM_ZERO]); IntrIdx++) 
    {
      attachInterruptFromConfig(MachEvntIntrpts[IntrIdx]);
    }
  }
  else
  {
    //
  }
}

// Function to attach an interrupt based on configuration passed
void attachInterruptFromConfig(const InterruptConfig_T &config) 
{
  attachInterrupt(digitalPinToInterrupt(config.pin), callbackFunctions[config.callbackIndex], config.mode);
}

//The IRAM_ATTR attribute ensures that the interrupt handler runs from the fast IRAM memory, 
//which is important for interrupt performance
void IRAM_ATTR HrzWrapStartEventCB(void)
{
  MachineEvent.MachineEvntFlg = true;
  MachineEvent.MachineEvent = EN_MACHINE_EVNT_HR_WRAP_STARTED;
}

void IRAM_ATTR UnloadingEventCB(void)
{
  MachineEvent.MachineEvntFlg = true;
  MachineEvent.MachineEvent = EN_MACHINE_EVNT_BALE_UNLOADING_DOWN;
}

void IRAM_ATTR ProxSnsrEvntCB(void)
{
  MachineEvent.MachineEvntFlg = true;
  MachineEvent.MachineEvent = EN_MACHINE_EVNT_PROXIMITY_SNSR;
}