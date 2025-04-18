#include "HW_Config.h"
 #include "HX711_lib.h"
 
 #define KNOWN_WEIGHT_IN_GRMS 5000.0
 
 void HX711Init(void);
 void OnTareSetBtnPress(void);
 void SetTare(void);
 void powerUp_hx711(void);
 void powerDown_hx711(void);
 // void waitForUserCalibCmd(En_SerialCmd);
 void SetScale(float);
 float CalculateCalibrationFactor(void);
 bool IsHx711PwrUp(void);
 float Get_WeightGrms(unsigned char);