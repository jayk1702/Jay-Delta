#include "HX711Module.h"

extern HX711 scale;

bool isPoweredUp_hx711 = false;
unsigned long powerUpTime_hx711 = 0;
float knownWeight = 0.0;
extern ConfigJson_T cnfgJsonData;

float Get_WeightGrms(unsigned char NoOfReadings)
{
  // float totalWeight = 0.0;
  // unsigned char NumOfRdngs = 0;
  
  // Take multiple readings and average them
  // for (NumOfRdngs = 0; NumOfRdngs < NUM_OF_READINGS; NumOfRdngs++) 
  // {
  //   totalWeight += scale.get_units(NUM_OF_READINGS);
  //   //delay(100);  // Wait 100ms between readings
  // }

  // return totalWeight/NUM_OF_READINGS; // Average reading from 10 samples

  float weight = 0.0;

  //This check is added to avoid infinite value
  //as if calibFactor zero then weight will be infinite
  if(scale.get_scale() > 0)
  {
    weight = scale.get_units(NoOfReadings);
  }
  else
  {
    weight = 0.0;
  }

  //return weight;
  return Get_RoundOffWeight(weight);
}

void SetTare(void)
{
  scale.tare();
  cnfgJsonData.TareOffsetVal = scale.get_offset();
  WriteDataToSpiffs(EN_TARE_OFFSET_SPIFFS, &cnfgJsonData);
#if ENABLE_DEBUG
  Serial.print("[INFO]Tare set with OFFSET value:");
  Serial.println(cnfgJsonData.TareOffsetVal);
#endif
}

float CalculateCalibrationFactor(void)
{
  float calibfactor = 0.0;
  long reading = 0.0;

  if (scale.is_ready()) 
  {
    scale.set_scale(); 

    Serial.println("[INFO]Please remove any weights from the scale and enter 'ok'");
    waitForUserCalibCmd(OK_SRL);

    scale.tare();
    Serial.println("[INFO]Tare done!");
    Serial.println("[INFO]Please enter a known weight in grams");
    waitForUserCalibCmd(WEIGHT_SRL);

    Serial.print("[INFO]Place ");
    Serial.print(knownWeight);
    Serial.println(" grams weight on the scale and enter 'ok'");
    waitForUserCalibCmd(OK_SRL);
    reading = scale.get_units(NUM_OF_READINGS);

    Serial.print("[INFO]Result: ");
    Serial.println(reading);

    calibfactor = reading/knownWeight;

    Serial.print("[INFO]calibfactor: ");
    Serial.println(calibfactor);

    Serial.println("[INFO]Please remove weights from scale and enter 'ok'");
    waitForUserCalibCmd(OK_SRL);

    scale.set_scale(calibfactor);
    SetTare();
    Serial.println("[INFO]Calibration completed successfully...!");
  } 
  else 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]HX711 not found.");
#endif
  }

  return calibfactor;
}

// Function to power up HX711
void powerUp_hx711(void) 
{
  scale.power_up();  // Wake up HX711
#if ENABLE_DEBUG
    Serial.println("[INFO]PowerUp HX711");
#endif  
  //powerUpTime_hx711 = millis();  // Record the time when the HX711 was powered up
  isPoweredUp_hx711 = true;  // Set the flag indicating HX711 is powered up
}

// Function to power down HX711
void powerDown_hx711(void) 
{
  scale.power_down();  // Put HX711 into low-power mode
#if ENABLE_DEBUG
    Serial.println("[INFO]PowerDown HX711");
#endif 
  isPoweredUp_hx711 = false; // Set the flag indicating HX711 is powered down
}

bool IsHx711PwrUp(void)
{
  return isPoweredUp_hx711;
}

void SetScale(float CalibFactor)
{
  scale.set_scale(CalibFactor);
#if ENABLE_DEBUG
  Serial.print("[INFO]SetScale_CalibFactor:");
  Serial.println(CalibFactor);
#endif
}

void SetTareOffset(long TareOffsetVal)
{
  scale.set_offset(TareOffsetVal);
#if ENABLE_DEBUG
  Serial.print("[INFO]SetTareOffset:");
  Serial.println(TareOffsetVal);
#endif
}

void HX711Init(void)
{
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);    //Setting the pins for the load cells
  SetScale(cnfgJsonData.LoadCellCalibFactor);
  SetTareOffset(cnfgJsonData.TareOffsetVal);
}