#include "HW_Config.h"

// Function to initialize the state machine
void InitStateMachine(void);
void SetMachineState(En_MachineStateEvent);
void HndleMachineEvents(void);
void PrintMachineStateDbg(En_MachineStateEvent);

// Function to get the current state
En_MachineStateEvent GetCurrentMachineState(void);
