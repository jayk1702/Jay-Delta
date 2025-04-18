#include "HW_Config.h"
#include "Interrupt.h"
#include "HX711Module.h"
#include "ExternalInterface.h"
#include "SpiffsOperations.h"
#include "MachineStateHndlr.h"
#include "HW_Timer.h"

#if GPS_ENABLE
#include "GPSModule.h"
#endif

#if DEVICE_ACTIVE_DBG_STS_ENB
// Variables to manage the blinking
unsigned long previousBlinkMillis = 0;  // stores the last time the LED was updated
const long blink_interval = 1000;         // interval at which to blink (milliseconds)
#endif

void setup() 
{
  BaleWrapStsBzrConfig();
  Serial.begin(115200);  // Set the baudrate at 115200
  //BaleWrapStsBzrConfig();
  ConfigRpiPowerRelayPins();
  turnOnRelay();
#if GPS_ENABLE
  setupGPSModule();
#endif

  if(!(setUpAndGetDataFromSpiffs() == EN_VALID_MACHINE_TYPE))
  {
    /*****Display Error Info******/
#if ENABLE_DEBUG
    Serial.println("[INFO]Undefined/Invalid machine type or spiffs operation failed");
#endif
    /*****Display Error Info******/
    //return;
  }

  TransmitPayloadOverSerial(EN_DEV_ATTR);

#ifdef ENABLE_LCD
  InitLCDModule();
#endif
  
  InitStateMachine();
  MachineEventPinsConfig();
  HwTimerIntrptConfig();
  HX711Init();

  MultiFuncBtnConfig();
  MultiFuncStsLEDConfig();
  

}

void loop() 
{
  HndleMachineEvents();
  
  MultiFuncBtnHndlr();

#if GPS_ENABLE
  GPSDataHndlr();
#endif

#if DEVICE_ACTIVE_DBG_STS_ENB
  blinkStatusLED();
#endif
  // UpdatePayloadDataAndTrnsmt();
  // delay(100);
}

#if DEVICE_ACTIVE_DBG_STS_ENB
// Function to blink the LED without using delay()
void blinkStatusLED(void)
{
  // Get the current time in milliseconds
  unsigned long currentMillis = millis();

  // Check if it's time to toggle the LED (i.e., if enough time has passed)
  if (currentMillis - previousBlinkMillis >= blink_interval) 
  {
    // Save the last time the LED was updated
    previousBlinkMillis = currentMillis;

    // Toggle the LED state
    //digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    Serial.println("[INFO]ESP32 ALIVE...");
  }
}
#endif