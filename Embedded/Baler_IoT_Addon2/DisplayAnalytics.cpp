#include "DisplayAnalytics.h"
#ifdef ENABLE_LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Initialize the LCD with I2C address (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif                               //ENABLE_LCD

extern BalerPayload_S BalerPayload;
BalerPayload_S *ptrBalerInfoDisplay = &BalerPayload;

extern ConfigJson_T cnfgJsonData;

String GetMachineTypeStr(En_BalerMachineType machType)
{
  String MachineType = "***";
  switch(machType)
  {
    case EN_MACHINE_TYPE_ASB:
      //Machine type is ASB
      MachineType = "ASB";
      break;

    case EN_MACHINE_TYPE_MSB:
      //Machine type is MSB
      MachineType = "MSB";
      break;

    case EN_MACHINE_TYPE_UNDEFINED:
      //Machine type undefined
      MachineType = "***";
      break;

    default:
      //Invalid machine type
      MachineType = "***";
      break;
  }
  return MachineType;
}



void InitLCDModule(void) {
  //Wire.begin(8, 9);  // Specify SDA and SCL pins if needed
  lcd.init();
  lcd.backlight();

  lcd.clear();
  
  DisplayAnalytics(BALE_INFO_DEAULT);
  delay(2000);

  DisplayAnalytics(BALE_INFO_ATTRIBUTES);
  delay(2000);

  // DisplayAnalytics(BALE_INFO_WEIGHT);
  // delay(2000);

  // DisplayAnalytics(BALE_INFO_COUNT);
  // delay(2000);

  // DisplayAnalytics(BALE_INFO_MOISTURE);
  // delay(2000);
}


void DisplayAnalytics(En_BaleInformation baleInfo) {
  lcd.clear();
  delay(500);

  switch (baleInfo) {
    case BALE_INFO_WEIGHT:
      lcd.setCursor(0, 0);
      lcd.print("Bales Weight & Count");

      lcd.setCursor(0, 1);
      lcd.print("Current : ");
      lcd.print(String(ptrBalerInfoDisplay->CurrBaleWeight_grms / 1000.0, 2));
      lcd.setCursor(18, 1);
      lcd.print(KILOGRAMS);

      lcd.setCursor(2, 2);
      lcd.print("Total : ");
      lcd.print(String(ptrBalerInfoDisplay->TotBaleWeight_grms / 1000.0, 2));
      lcd.setCursor(18, 2);
      lcd.print(KILOGRAMS);

      lcd.setCursor(2, 3);
      lcd.print("Bales : ");
      lcd.print(String(ptrBalerInfoDisplay->TotBaleCount));

      //delay(500);
      break;

    case BALE_INFO_COUNT:
      lcd.setCursor(5, 0);
      lcd.print("Count Info");

      lcd.setCursor(0, 1);
      lcd.print("Total Bale : ");
      lcd.print(String(ptrBalerInfoDisplay->TotBaleCount));

      lcd.setCursor(1, 2);
      lcd.print("Bale Wrap : ");
      lcd.print(String(ptrBalerInfoDisplay->CurrBaleWrapCount));

      //delay(500);
      break;

    case BALE_INFO_MOISTURE:
      lcd.setCursor(6, 0);
      lcd.print("Moisture");

      lcd.setCursor(0, 1);
      lcd.print("Moisture % : ");
      lcd.print(String(ptrBalerInfoDisplay->MoistureLevel));

      //delay(500);
      break;

    case BALE_INFO_DEAULT:
      lcd.setCursor(6, 0);
      lcd.print("CORNEXT");
      lcd.setCursor(0, 1);
      lcd.print("DELTA THINGS Pvt Ltd");
      lcd.setCursor(4, 2);
      lcd.print("Silage Baler");
      lcd.setCursor(1, 3);
      lcd.print(BALER_DEVICE_NAME);      
      lcd.setCursor(16, 3);
      lcd.print(GetMachineTypeStr(cnfgJsonData.MachineType));

      //delay(500);
      break;

    case BALE_INFO_ERROR:

      lcd.setCursor(6, 0);
      lcd.print("ERROR");

      //delay(500);
      break;

    case BALE_INFO_ATTRIBUTES:
      lcd.setCursor(6, 0);
      lcd.print(BALER_DEVICE_NAME); 

      lcd.setCursor(0, 1); 
      lcd.print("Machine Type : ");
      lcd.print(GetMachineTypeStr(cnfgJsonData.MachineType));

      lcd.setCursor(0, 2); 
      lcd.print("Max Wrap Cnt : ");
      lcd.print(String(cnfgJsonData.ThresholdWrapCount));

      lcd.setCursor(0, 3); 
      lcd.print("Calib Factor : ");
      lcd.print(String(cnfgJsonData.LoadCellCalibFactor));

      break;

  }
}
