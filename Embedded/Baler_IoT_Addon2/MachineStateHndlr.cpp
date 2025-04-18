#include "MachineStateHndlr.h"

En_MachineStateEvent CurrMachineState = EN_MACHINE_STATE_UNDEFINED;

MachineEvent_T MachineEvent = {false, EN_MACHINE_EVNT_UNDEFINED};

extern bool getWeightAndTrnsmtPayld;

// Function to initialize the state machine
void InitStateMachine(void) 
{
  SetMachineState(EN_MACHINE_STATE_IDLE);
}

// Function to get the machine's current state
En_MachineStateEvent GetCurrentMachineState(void) 
{
  return CurrMachineState;
}

// Function to set the machine's state
void SetMachineState(En_MachineStateEvent state)
{
  CurrMachineState = state;
#if ENABLE_DEBUG
  PrintMachineStateDbg(CurrMachineState);
#endif
}

void HndleMachineEvents(void)
{
  if(MachineEvent.MachineEvntFlg == true)
  {
    switch(MachineEvent.MachineEvent)
    {
      case EN_MACHINE_EVNT_HR_WRAP_STARTED:
        SetMachineState(EN_MACHINE_STATE_HR_WRAP_STARTED);
        break;

      case EN_MACHINE_EVNT_BALE_UNLOADING_DOWN:
        SetMachineState(EN_MACHINE_STATE_BALE_UNLOADING_DOWN);
        //UpdatePayloadDataAndTrnsmt();
        getWeightAndTrnsmtPayld = true;
        break;

      case EN_MACHINE_EVNT_PROXIMITY_SNSR:
        ProxSnsrEvntHndlr();
        break;

      default:
        SetMachineState(EN_MACHINE_STATE_UNDEFINED);
        break;
    }

    MachineEvent.MachineEvntFlg = false;
    MachineEvent.MachineEvent = EN_MACHINE_EVNT_UNDEFINED;
  }

  HasTimerExpired();

  WrapCountStsLEDandBzrHndlr();

  fetchStableWeightAndTrnsmtPayload();
}

void PrintMachineStateDbg(En_MachineStateEvent CurrMachState)
{
  switch(CurrMachState)
  {
    case EN_MACHINE_STATE_IDLE:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_IDLE");
      break;

    case EN_MACHINE_STATE_FEEDING_STARTED:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_FEEDING_STARTED");
      break;

    case EN_MACHINE_STATE_FEEDING_COMPLETE:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_FEEDING_COMPLETE");
      break;

    case EN_MACHINE_STATE_VR_WRAP_SQUEEZ:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_VR_WRAP_SQUEEZ");
      break;

    case EN_MACHINE_STATE_VR_WRAP_EXPAND:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_VR_WRAP_EXPAND");
      break;

    case EN_MACHINE_STATE_CHAMBER_OPENED:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_CHAMBER_OPENED");
      break;

    case EN_MACHINE_STATE_CHAMBER_CLOSED:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_CHAMBER_CLOSED");
      break;

    case EN_MACHINE_STATE_HR_WRAP_STARTED:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_HR_WRAP_STARTED");
      break;

    case EN_MACHINE_STATE_HR_WRAP_COMPLETED:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_HR_WRAP_COMPLETED");
      break;

    case EN_MACHINE_STATE_WRAP_CUT_UP:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_WRAP_CUT_UP");
      break;

    case EN_MACHINE_STATE_WRAP_CUT_DOWN:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_WRAP_CUT_DOWN");
      break;

    case EN_MACHINE_STATE_BALE_UNLOADING_DOWN:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_BALE_UNLOADING_DOWN");
      break;

    case EN_MACHINE_STATE_BALE_LOADING_UP:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_BALE_LOADING_UP");
      break;

    default:
      Serial.println("[INFO]MachineState: EN_MACHINE_STATE_UNDEFINED");
      break;
  }
}
