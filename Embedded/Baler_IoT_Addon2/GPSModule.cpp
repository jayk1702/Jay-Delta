#include "GPSModule.h"

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
HardwareSerial GPSserial(SERIAL_1);

unsigned long lastGPSUpdate = 0;
unsigned long prevMillisNoGPSDtctd = 0;  // stores the last time we checked for GPS data
unsigned long GPSdataLastRcvdTime = 0;

bool GPSHeartBeatSts = false;

CurrentGPSdata_T CurrrentGPSInfo = {0.0, 0.0};

void setupGPSModule(void)
{
  pinMode(GPS_PWR_EN, OUTPUT);
  pinMode(GPS_RST_EN, OUTPUT);
  digitalWrite(GPS_PWR_EN, HIGH);
  digitalWrite(GPS_RST_EN, LOW);
  GPSserial.begin(GPS_SERIAL_BAUDRATE,SERIAL_8N1,GPS_TX_PIN,GPS_RX_PIN);
  GPSdataLastRcvdTime = millis();
}

void GPSDataHndlr(void)
{
  // GPS Task (runs every gpsInterval)
  unsigned long currMillis = 0.0;

  currMillis = millis();
  if (currMillis - lastGPSUpdate >= GPS_DATA_UPDATE_INTERVAL) 
  {
    lastGPSUpdate = currMillis;
    readGPSData();
  }

  // currMillis = millis();
  // if ( (currMillis -  prevMillisNoGPSDtctd >= 5000) && (gps.charsProcessed() < 10) )
  // {
  //   prevMillisNoGPSDtctd = currMillis;
  //   Serial.println(F("No GPS detected: check wiring."));
  //   //while(true);
  //   // currMillisNoGPSDtctd = millis();

  //   // // Check if a second has passed since the last check
  //   // if (currMillisNoGPSDtctd - prevMillisNoGPSDtctd >= interval) 
  //   // {
  //   //     prevMillisNoGPSDtctd = currMillisNoGPSDtctd;  // save the last time we checked

  //   //     // Print the error message
  //   //     Serial.println(F("No GPS detected: check wiring."));
  //   // }
  // }

  // Check if there has been no data for the specified timeout
  currMillis = millis();
  if (currMillis - GPSdataLastRcvdTime > NO_GPS_DATA_RECEIVED_INTERVAL) 
  {
    GPSdataLastRcvdTime = currMillis;
    GPSHeartBeatSts = false;
#if ENABLE_DEBUG 
    //Serial.println("[INFO]No GPS data received, device may be powered off or no data sending.");
#endif
  }
}

void readGPSData(void)
{
  while (GPSserial.available() > 0) 
  {
    GPSdataLastRcvdTime = millis();
    GPSHeartBeatSts = true;
    if (gps.encode(GPSserial.read())) 
    {
			GetAndUpdateGPSDataStruct();
		}
  }

  // if (gps.location.isUpdated())
  // {
  //   GPSInfo.latitude = gps.location.lat();
  //   Serial.print("[INFO]Latitude= ");
  //   Serial.print(GPSInfo.latitude);
  //   GPSInfo.longitude = gps.location.lng();
  //   Serial.print(" Longitude= ");
  //   Serial.println(GPSInfo.longitude);
  // }

  // if (gps.altitude.isUpdated()) 
  // {
  //   Serial.print("Altitude= ");
  //   Serial.println(gps.altitude.meters());
  // }
}

void GetAndUpdateGPSDataStruct(void)
{
  //if (gps.location.isValid())
  {
    CurrrentGPSInfo.latitude = gps.location.lat();
    CurrrentGPSInfo.longitude = gps.location.lng();
#if ENABLE_DEBUG
    // Serial.print("Latitude= ");
    // Serial.print(CurrrentGPSInfo.latitude, 6);
    // Serial.print(" Longitude= ");
    // Serial.println(CurrrentGPSInfo.longitude, 6);
#endif
	} 
  // else 
  // {
	// 	Serial.println(F("INVALID GPS Data Received"));
	// }

	// Serial.print(F("  Date/Time: "));
	// if (gps.date.isValid()) 
  // {
	// 	Serial.print(gps.date.month());
	// 	Serial.print(F("/"));
	// 	Serial.print(gps.date.day());
	// 	Serial.print(F("/"));
	// 	Serial.print(gps.date.year());
	// } 
  // else 
  // {
	// 	Serial.print(F("INVALID"));
	// }

	// Serial.print(F(" "));
	// if (gps.time.isValid()) 
  // {
	// 	if (gps.time.hour() < 10) Serial.print(F("0"));
	// 	Serial.print(gps.time.hour());
	// 	Serial.print(F(":"));
	// 	if (gps.time.minute() < 10) Serial.print(F("0"));
	// 	Serial.print(gps.time.minute());
	// 	Serial.print(F(":"));
	// 	if (gps.time.second() < 10) Serial.print(F("0"));
	// 	Serial.print(gps.time.second());
	// 	Serial.print(F("."));
	// 	if (gps.time.centisecond() < 10) Serial.print(F("0"));
	// 	Serial.print(gps.time.centisecond());
	// } 
  // else 
  // {
	// 	Serial.print(F("INVALID"));
	// }
}

double GetLatitude(void)
{
  return  CurrrentGPSInfo.latitude;
}

double GetLongitude(void)
{
  return  CurrrentGPSInfo.longitude;
}

bool GetGPSHeartBeatSts(void)
{
  return GPSHeartBeatSts;
}