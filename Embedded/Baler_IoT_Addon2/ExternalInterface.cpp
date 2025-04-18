#include "ExternalInterface.h"

bool MultiFunBtnCurState = LOW;  // Stores the current state of the button
bool MultiFunBtnLastState = LOW;  // Stores the last state of the button
bool MultiFunBtnPrsd = false;  // Tracks the button press state
bool MultiFunBtnlongPress = false;  // Tracks if it's a long press
bool IsDeviceInCmdMode = false;
bool getWeightAndTrnsmtPayld = false;
bool ProxSnsrEvntDtctd = false;
bool MultiFunLEDCurState = false;  // Stores the current state of the LED
bool IsLEDONDueToWrpCntExcd = false;

En_SerialCmd serialCmdEvent = UNDEFINED_SRL;

En_BaleWrapState BaleWrapSt = UNDEFINED;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long prevMillisBaleWrap = 0;
unsigned long PrevMillisPwrUpHx711 = 0;
unsigned long prevMillisMultiFuncStsLED = 0;  // Stores the last time the LED was updated
unsigned long MultiFunBtnPressStartTime = 0;  // Stores the time when the button press started

static unsigned char ProxEventCount = 0;
static unsigned short BaleCount = 0;
static float TotalBaleWeight_grms = 0.0;

extern BalerPayload_S *ptrBalerPayload;
extern bool IsTimerStopped;
extern float knownWeight;
extern ConfigJson_T cnfgJsonData;

void MultiFuncBtnConfig(void)
{
  pinMode(MULTI_FUNC_BTN_PIN, INPUT_PULLUP);
}

void MultiFuncStsLEDConfig(void)
{
  pinMode(MULTI_FUNC_STATUS_LED_PIN, OUTPUT);
  digitalWrite(MULTI_FUNC_STATUS_LED_PIN, LOW);   // Turn LED off by default
}

void BaleWrapStsBzrConfig(void)
{
  pinMode(BALE_WRAP_STATUS_BZR_PIN_RELAY_1, OUTPUT);
  digitalWrite(BALE_WRAP_STATUS_BZR_PIN_RELAY_1, LOW);   // Turn OFF BUZZER by default
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_2, LOW);   // Turn OFF BUZZER by default

}

void MultiFuncBtnHndlr(void)
{
  unsigned long CurrMillis = 0.0;

  // Read the current button state
  MultiFunBtnCurState = digitalRead(MULTI_FUNC_BTN_PIN);

  // Detect a button press
  if (MultiFunBtnCurState == LOW && MultiFunBtnLastState == HIGH) 
  {
    MultiFunBtnPressStartTime = millis();  // Record the start time of the button press
    MultiFunBtnPrsd = true;  // Button is pressed
    MultiFunBtnlongPress = false;  // Reset long press detection
  }

  // Detect button release
  if (MultiFunBtnCurState == HIGH && MultiFunBtnLastState == LOW) 
  {
    if (MultiFunBtnPrsd) 
    {
      CurrMillis = millis();

      if (CurrMillis - MultiFunBtnPressStartTime/*pressDuration*/ >= MULTI_FUNC_BTN_LONG_PRESS_TIME) 
      {
        //OnMultiFuncBtnLongPress();  // Long press detected
      } 
      //else if(CurrMillis - MultiFunBtnPressStartTime/*pressDuration*/ < 1000)
      else
      {
        OnMultiFuncBtnShortPress();  // Short press detected
      }
      MultiFunBtnPrsd = false;  // Reset the button press state
    }
    MultiFunBtnPressStartTime = 0.0;
  }

  //If the button is still pressed, check for long press
  if (MultiFunBtnPrsd) 
  {
    if (millis() - MultiFunBtnPressStartTime/*pressDuration*/ >= MULTI_FUNC_BTN_LONG_PRESS_TIME && !MultiFunBtnlongPress) 
    {
      MultiFunBtnlongPress = true;
      OnMultiFuncBtnLongPress();  // Execute long press function if press exceeds threshold
    }
  }
  // Update the last button state for next loop iteration
  MultiFunBtnLastState = MultiFunBtnCurState;
}

void MultiFuncLEDStateHndlr(void)
{
  unsigned long currentMillis = 0;

  if(IsDeviceInCmdMode)
  {
    currentMillis = millis();  // Get the current time in milliseconds
  
    // Check if 100 milliseconds have passed
    if (currentMillis - prevMillisMultiFuncStsLED >= MULTI_FUNC_STATUS_LED_INTERVAL) 
    {
      // Save the last time the LED was updated
      prevMillisMultiFuncStsLED = currentMillis;
      // If the LED is on, turn it off, and vice versa
      digitalWrite(MULTI_FUNC_STATUS_LED_PIN, !digitalRead(MULTI_FUNC_STATUS_LED_PIN));  // Toggle LED
    }
  }
  else
  {
    if(digitalRead(MULTI_FUNC_STATUS_LED_PIN) == HIGH)
    {
      digitalWrite(MULTI_FUNC_STATUS_LED_PIN, LOW);
    }
  }
}

// Function for short press
void OnMultiFuncBtnShortPress(void) 
{
  powerUp_hx711();
  delay(100);
  SetTare();
  TransmitPayloadOverSerial(EN_DEV_ATTR);
  powerDown_hx711();
  delay(100);
}

// Function for long press
void OnMultiFuncBtnLongPress(void) 
{
  serialCmdEvent = MAIN_MENU_OPT_SEL_SRL;
#if ENABLE_SRL_CMD_DBG
  DisplayMainMenu();
#endif

  powerUp_hx711();
  delay(100);
  SerialCommandsHandlr();
  powerDown_hx711();
  delay(100);
}

void DisplayMainMenu(void)
{
  Serial.println("\n****************CURRENT CONFIGURATIONS****************");
  Serial.println("[INFO]Current Configurations:");
  Serial.print("[INFO]MachineType:");
  Serial.println(cnfgJsonData.MachineType);
  Serial.print("[INFO]LoadCellCalibFactor:");
  Serial.println(cnfgJsonData.LoadCellCalibFactor);
  Serial.print("[INFO]ThresholdWrapCount:");
  Serial.println(cnfgJsonData.ThresholdWrapCount);
  Serial.print("[INFO]TareOffsetVal:");
  Serial.println(cnfgJsonData.TareOffsetVal);
  Serial.println("****************CURRENT CONFIGURATIONS****************\n");

  Serial.println("[INFO]Please Select any option below:");
  Serial.println("[Ex: Enter '2' to update weight calibration factor]");
  Serial.println("1. Update machine type");
  Serial.println("2. Update weight calibration factor"); 
  Serial.println("3. Update wrap count");
  Serial.println("4. Exit");
}

void SerialCommandsHandlr(void)
{
  bool breakLoop = false;
  unsigned char BaleWrapCount = 0;

  while(!breakLoop)
  {
    IsDeviceInCmdMode = true;
    MultiFuncLEDStateHndlr();
    // Check if data is available to read
    if (Serial.available() > 0) 
    {
      String incomingString = Serial.readStringUntil('\n');  // Read the incoming string until a newline character

      Serial.print("[INFO]Serial Data Received:");
      Serial.println(incomingString);

      switch(serialCmdEvent)
      {
        case CMD_PRMPT_SRL:
LABEL_CMD_PRMPT:
#if ENABLE_SRL_CMD_DBG
          Serial.println("[INFO]Please select any option:");
          Serial.println("1. Main Menu");
          Serial.println("2. Exit");
#endif
          serialCmdEvent = MAIN_MENU_OPT_SRL;
          break;

        case MAIN_MENU_OPT_SRL:
          if(incomingString == "1")
          {
LABEL_MAIN_MENU:
#if ENABLE_SRL_CMD_DBG
            DisplayMainMenu();
#endif
            serialCmdEvent = MAIN_MENU_OPT_SEL_SRL;  
          }
          else if(incomingString == "2")
          {
            breakLoop = true;
          }
          else
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter a valid command");
#endif
            serialCmdEvent = CMD_PRMPT_SRL;
            goto LABEL_CMD_PRMPT;
          }
          break;

        case MAIN_MENU_OPT_SEL_SRL:
          if(incomingString == "1")
          {
LABEL_MACHTYPE_MENU_SRL:
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Select the machine type:");
            Serial.println("[Ex: Enter '1' to select machine type as MSB]");
            Serial.println("1. MSB");
            Serial.println("2. ASB");
            Serial.println("3. Exit");
#endif
            serialCmdEvent = MACH_TYPE_SRL;
          }
          else if(incomingString == "2")
          {
            cnfgJsonData.LoadCellCalibFactor = CalculateCalibrationFactor();
            SetScale(cnfgJsonData.LoadCellCalibFactor);
            WriteDataToSpiffs(EN_CALIB_FACTOR_SPIFFS, &cnfgJsonData);
            TransmitPayloadOverSerial(EN_DEV_ATTR);
            DisplayAnalytics(BALE_INFO_ATTRIBUTES);
            serialCmdEvent = CMD_PRMPT_SRL;
            goto LABEL_CMD_PRMPT;
          }
          else if(incomingString == "3")
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter the bale wrap count");
#endif
            serialCmdEvent = WRAP_COUNT_SRL;
          }
          else if(incomingString == "4")
          {
            breakLoop = true;
          }
          else
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter a valid option");
#endif
            serialCmdEvent = MAIN_MENU_OPT_SRL;
            goto LABEL_MAIN_MENU;
          }
          break;

        case WRAP_COUNT_SRL:
          BaleWrapCount = incomingString.toInt();
          if(BaleWrapCount > 0)
          {
            cnfgJsonData.ThresholdWrapCount = BaleWrapCount;
            WriteDataToSpiffs(EN_WRAP_COUNT_SPIFFS, &cnfgJsonData);
            DisplayAnalytics(BALE_INFO_ATTRIBUTES);
            serialCmdEvent = CMD_PRMPT_SRL;
            goto LABEL_CMD_PRMPT;
          }
          else
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter a valid non-zero positive value");
#endif
          }
          break;

        case MACH_TYPE_SRL:
          if(incomingString == "1")
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]MachineType updating as MSB...!");
#endif
            cnfgJsonData.MachineType = EN_MACHINE_TYPE_MSB;
            WriteDataToSpiffs(EN_MACHINE_TYPE_SPIFFS, &cnfgJsonData);
            DisplayAnalytics(BALE_INFO_ATTRIBUTES);
            serialCmdEvent = CMD_PRMPT_SRL;
            goto LABEL_CMD_PRMPT;
          }
          else if(incomingString == "2")
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]MachineType updating as ASB...!");
#endif
            cnfgJsonData.MachineType = EN_MACHINE_TYPE_ASB;
            WriteDataToSpiffs(EN_MACHINE_TYPE_SPIFFS, &cnfgJsonData);
            DisplayAnalytics(BALE_INFO_ATTRIBUTES);
            serialCmdEvent = CMD_PRMPT_SRL;
            goto LABEL_CMD_PRMPT;
          }
          else if(incomingString == "3")
          {
            breakLoop = true;
          }
          else
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter a valid option");
#endif
            serialCmdEvent = MAIN_MENU_OPT_SEL_SRL;
            goto LABEL_MACHTYPE_MENU_SRL;
          }
          
          break;

        default:
#if ENABLE_SRL_CMD_DBG
          Serial.println("[INFO]Invalid command");
#endif
          breakLoop = true;
          break;
      }

      if(breakLoop)
      {
        IsDeviceInCmdMode = false;
        break;
      }
    }
  }
#if ENABLE_SRL_CMD_DBG
  Serial.println("[INFO]Loop Exited...!");
#endif
  MultiFuncLEDStateHndlr();
}

void waitForUserCalibCmd(En_SerialCmd cmd)
{
  bool breakLoop = false;
  unsigned int weightInGrms = 0;
  String incomingString = "";

  while(!breakLoop)
  {
    MultiFuncLEDStateHndlr();
    // Check if data is available to read
    if (Serial.available() > 0) 
    {
      incomingString = Serial.readStringUntil('\n');  // Read the incoming string until a newline character
#if ENABLE_SRL_CMD_DBG
      Serial.print("[INFO]Serial Data Received:");  // Print a confirmation message to the serial monitor
      Serial.println(incomingString);
#endif
      switch(cmd)
      {
        case OK_SRL:
          // Check if the received string is "ok"
          if (incomingString == "ok") 
          {
            breakLoop = true;
          }
          break;

        case WEIGHT_SRL:
          weightInGrms = incomingString.toInt();
          if(weightInGrms > 0)
          {
            knownWeight = (float)weightInGrms;
            breakLoop = true;
          }
          else
          {
#if ENABLE_SRL_CMD_DBG
            Serial.println("[INFO]Please enter a valid non-zero positive value in grams");
#endif
          }
          break;

        default:
#if ENABLE_SRL_CMD_DBG
          Serial.println("[INFO]Invalid command");
#endif
          break;
      }

      if(breakLoop)
      {
        break;
      }
    }
  }
}

float Get_RoundOffWeight(float actualWeight_grm)
{
  static float roundOffWeight_grm = 0.0;

  //Bale weight making to 0 to overcome minor fluctuations at 0 weight
  if ((actualWeight_grm < MAX_OFFSET_VALUE_AT_ZERO_WEIGHT) && (actualWeight_grm > MIN_OFFSET_VALUE_AT_ZERO_WEIGHT)) 
  {
    actualWeight_grm = 0.00;
  }

  // if(actualWeight_grm > roundOffWeight_grm)
  // {
  //     if((actualWeight_grm - roundOffWeight_grm) > WEIGHT_ROUNDOFF_OFFSET_VALUE)
  //     {
  //         roundOffWeight_grm = actualWeight_grm;
  //     }
  // }
  // else
  // {
  //     if((roundOffWeight_grm - actualWeight_grm) > WEIGHT_ROUNDOFF_OFFSET_VALUE)
  //     {
  //         roundOffWeight_grm = actualWeight_grm;
  //     }
  // }

  // return roundOffWeight_grm;

  return actualWeight_grm;
}

void ProxSnsrEvntHndlr()
{
  ProxEventCount++;
#if ENABLE_DEBUG
  Serial.print("[INFO]ProxSnsr event detected. ProxEventCount:");
  Serial.println(ProxEventCount);
#endif
  //update machine state for MSB
  if(Get_MachineType() == EN_MACHINE_TYPE_MSB)
  {
    if(ProxEventCount == NUM_ONE)
    {
      SetMachineState(EN_MACHINE_STATE_HR_WRAP_STARTED);
    }
    else if(ProxEventCount == cnfgJsonData.ThresholdWrapCount)
    {
      /********Write buzzer and led logic here********/
      BaleWrapSt = BALE_WRAP_COUNT_REACHED;
#if ENABLE_DEBUG
      Serial.print("[INFO]Baler wrap count reached the target count:");
      Serial.println(ProxEventCount);
#endif
    }
    else
    {
      //
    }
  }

  ProxSnsrEvntDtctd = true;

  ResetTimerValue(EN_MACHINE_EVNT_PROXIMITY_SNSR);

  if(IsTimerStopped)
  {
    StartTimer(EN_MACHINE_EVNT_PROXIMITY_SNSR);
    IsTimerStopped = false;
  }

#if ENABLE_DEBUG
    // Serial.print("[INFO]CurrentWeightInGrms:");
    // Serial.println(Get_WeightGrms(NUM_ONE));
#endif

}

void HndlBaleDataOnProxSnsrTmrExprd(void)
{
  if (ProxEventCount >= cnfgJsonData.ThresholdWrapCount)
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]Assuming Baler Horizontal Wrap Completed!");
#endif
    //BaleCount++;
    //getWeightAndTrnsmtPayld = true;
    //Note: Updating wrap complete status manually, assuming there is no event from the machine
    SetMachineState(EN_MACHINE_STATE_HR_WRAP_COMPLETED);
    // if(Get_MachineType() == EN_MACHINE_TYPE_MSB)
    // {
    //   UpdatePayloadDataAndTrnsmt();
    //   //Turn OFF BaleWrap status LED after trnsmtng payload 
    //   TurnOFFMultiFuncStatusLED();
    // }
  }
  else
  {
    //TODO:What is the plan of action in this case???
    //What is the state of machine???
    //getWeightAndTrnsmtPayld = true;
#if ENABLE_DEBUG
    Serial.print("[INFO]Bale Wrap stopped and not reached the target count. WrapCount:");
    Serial.print(ProxEventCount);
    Serial.print(" BaleCount:");
    Serial.println(BaleCount);
#endif
    //TODO:Should we reset??
    //ProxEventCount = 0;
  }
  BaleCount++;
  getWeightAndTrnsmtPayld = true;
}

void UpdatePayloadDataAndTrnsmt(void)
{
  float CurBaleWeightGrms = 0.0;

  CurBaleWeightGrms = Get_WeightGrms(NUM_OF_READINGS); //Get weight from HX711

  TotalBaleWeight_grms += CurBaleWeightGrms;

  ptrBalerPayload->CurrBaleWeight_grms = CurBaleWeightGrms;
  ptrBalerPayload->TotBaleWeight_grms = TotalBaleWeight_grms;
  ptrBalerPayload->CurrBaleWrapCount = ProxEventCount;
  ptrBalerPayload->TotBaleCount = BaleCount;
#if GPS_ENABLE
  ptrBalerPayload->latitude = GetLatitude();
  ptrBalerPayload->longitude = GetLongitude();
  ptrBalerPayload->GPSHeartBeatSts = GetGPSHeartBeatSts();
#endif
  TransmitPayloadOverSerial(EN_DEV_ANL);
  DisplayAnalytics(BALE_INFO_WEIGHT);

  //Reset count
  ProxEventCount = 0;
}

void WrapCountStsLEDandBzrHndlr(void)
{
  if(BaleWrapSt == BALE_WRAP_COUNT_REACHED)
  {
    digitalWrite(MULTI_FUNC_STATUS_LED_PIN, HIGH);  // Turn ON LED
    digitalWrite(BALE_WRAP_STATUS_BZR_PIN_RELAY_1, HIGH);  // Turn ON BUZZER
    prevMillisBaleWrap = millis();   // Record the time when LED was turned on
    BaleWrapSt = BALE_WRAP_BZR_HIGH;  // Set the LED state to off

    //Making false to prevent LED off in case of ThresholdWrapCount reached
    IsLEDONDueToWrpCntExcd = true;
  }

  // Check if 3 seconds have passed
  if ((BaleWrapSt == BALE_WRAP_BZR_HIGH) && ((millis() - prevMillisBaleWrap) >= BALE_WRAP_STATUS_BZR_ON_TIME)) 
  {
    // Turn off the Buzzer after 3 seconds
    digitalWrite(BALE_WRAP_STATUS_BZR_PIN_RELAY_1, LOW);  // Turn OFF BUZZER
    BaleWrapSt = BALE_WRAP_BZR_LOW;
  }

  if(ProxSnsrEvntDtctd && !IsLEDONDueToWrpCntExcd)
  {
    if(!MultiFunLEDCurState)
    {
      digitalWrite(MULTI_FUNC_STATUS_LED_PIN, HIGH);  // Turn ON LED
      MultiFunLEDCurState = true;
      prevMillisMultiFuncStsLED = millis();
    }

    // Check if the LED has been ON for 100 ms
    if ( (MultiFunLEDCurState && millis() - prevMillisMultiFuncStsLED >= MULTI_FUNC_STATUS_LED_INTERVAL) )
    {
      MultiFunLEDCurState = false;
      digitalWrite(MULTI_FUNC_STATUS_LED_PIN, LOW);  // Turn off the LED
      ProxSnsrEvntDtctd = false;
    }
  }
}

void fetchStableWeightAndTrnsmtPayload(void)
{
  if(getWeightAndTrnsmtPayld)
  {
    powerUp_hx711();
    PrevMillisPwrUpHx711 = millis();
    getWeightAndTrnsmtPayld = false;
  }

  if ( IsHx711PwrUp() && ((millis() - PrevMillisPwrUpHx711) >= POWER_UP_DELAY_HX711))
  {
    UpdatePayloadDataAndTrnsmt();

    if(Get_MachineType() == EN_MACHINE_TYPE_MSB)
    {
      //Turn OFF BaleWrap status LED after trnsmtng payload 
      TurnOFFMultiFuncStatusLED();
      IsLEDONDueToWrpCntExcd = false;
    }
    powerDown_hx711();
  }
}

void TurnOFFMultiFuncStatusLED(void)
{
  digitalWrite(MULTI_FUNC_STATUS_LED_PIN, LOW);   // Turn OFF LED
}

void ConfigRpiPowerRelayPins(void)
{
  pinMode(RELAY_PIN_A_RPI_POWER, OUTPUT);
  pinMode(RELAY_PIN_B_RPI_POWER, OUTPUT);
}

void turnOnRelay(void)
{
  digitalWrite(RELAY_PIN_A_RPI_POWER, HIGH); 
  delay(2); //2ms pulse signal 
  digitalWrite(RELAY_PIN_A_RPI_POWER, LOW);
}

void turnOffRelay(void)
{
  digitalWrite(RELAY_PIN_B_RPI_POWER, HIGH);
  delay(2);//2ms pulse signal 
  digitalWrite(RELAY_PIN_B_RPI_POWER, LOW);
}