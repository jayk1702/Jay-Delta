#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_

#include <Arduino.h>
#include "Common.h"

#define MULTI_FUNC_BTN_PIN                0 //Use for shortPress(Tare), longPress(MachTyp,Calib,WrapCount)
#define BATTERY_MONITOR_PIN               1
#define PROX_SEN_EVENT_PIN                4
#define HRZ_WRAP_START_EVENT_PIN          5
#define UNLOADING_EVENT_PIN               6
#define ASB_AUTO_MANUAL_OPMODE_PIN        7
#define BALE_WRAP_STATUS_BZR_PIN_RELAY_1  12 //15  //NOTE: To use this pin remove R56(0 ohm) and place R2(0 ohm) on HW revision 1.0.4
#define RELAY_2                           13 //16  //NOTE: To use this pin remove R58(0 ohm) and place R63(0 ohm) on HW revision 1.0.4
#define GPS_RX_PIN                        17  //(ESP32-S3_UART1_TX)
#define GPS_TX_PIN                        18  //(ESP32-S3_UART1_RX)
#define MAX485_DE_RE                      21
#define MULTI_FUNC_STATUS_LED_PIN         38  //BuiltIn-LED
#define LOADCELL_DOUT_PIN                 39  //Data Pin for Load cell
#define LOADCELL_SCK_PIN                  40  //Clock Pin for Load Cell
#define RASPBERRY_PI_TX_PIN               44  //(ESP32-S3_UART0_RX)            
#define RASPBERRY_PI_RX_PIN               43  //(ESP32-S3_UART0_TX)
#define RELAY_PIN_A_RPI_POWER             47  //To turn ON Rpi
#define RELAY_PIN_B_RPI_POWER             48  //To turn OFF Rpi
#define GPS_PWR_EN                        10  //To turn ON GPS
#define GPS_RST_EN                        11  //To turn ON GPS


#endif //_HW_CONFIG_H_