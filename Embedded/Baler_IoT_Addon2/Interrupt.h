#include "HW_Config.h"

// Define a structure to hold pin, callback, and mode
typedef struct 
{
  unsigned char pin;                    // Pin number
  unsigned char callbackIndex;          // Index of the callback function in the array
  unsigned char mode;                   // Interrupt mode (e.g., RISING, FALLING, CHANGE)
}InterruptConfig_T;

void MachineEventPinsConfig(void);
// Function prototype to attach interrupts using structure
void attachInterruptFromConfig(const InterruptConfig_T &config);

/*****************CallBack Functions*******************/
void IRAM_ATTR HrzWrapStartEventCB(void);
void IRAM_ATTR UnloadingEventCB(void);
void IRAM_ATTR ProxSnsrEvntCB(void);
/*****************CallBack Functions*******************/