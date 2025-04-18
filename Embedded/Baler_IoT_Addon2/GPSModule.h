#include "TinyGPSPlus.h"
#include <HardwareSerial.h>
#include "HW_Config.h"

#define GPS_SERIAL_BAUDRATE 9600
#define SERIAL_0 0
#define SERIAL_1 1

#define GPS_DATA_UPDATE_INTERVAL 1000 //ms
#define NO_GPS_DATA_RECEIVED_INTERVAL 5000  //ms

typedef struct
{
  double latitude;
  double longitude;
}CurrentGPSdata_T;

void setupGPSModule(void);
void GPSDataHndlr(void);
void readGPSData(void);
void GetAndUpdateGPSDataStruct(void);
double GetLatitude(void);
double GetLongitude(void);
bool GetGPSHeartBeatSts(void);
