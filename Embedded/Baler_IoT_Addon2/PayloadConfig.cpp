#include "PayloadConfig.h"

BalerPayload_S BalerPayload = { 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0 ,0};

BalerPayload_S *ptrBalerPayload = &BalerPayload;

extern ConfigJson_T cnfgJsonData;

//Calculate the checksum of data, byte by byte using XOR operation
//before calculation, exclude "$" and "*" from the string
int PayloadChecksumCalculate(String payloadToChecksum) 
{
  int checksum = 0x00;
  //fetch data which is between "$" and "*" as a substring from payload data
  String StrToChecksumCal = payloadToChecksum.substring(payloadToChecksum.indexOf(PAYLOAD_BEGIN) + 1, payloadToChecksum.indexOf(PAYLOAD_ASTERISK));
  //get the length of the payload data excluding "$" and "*"
  int len = StrToChecksumCal.length();
  //assign substring as a c string to a char pointer
  const char *StrByteArray = StrToChecksumCal.c_str();
  //find checksum of substing, each byte by byte XOR op
  for (int i = 0; i < len; i++) {
    checksum ^= StrByteArray[i];
  }
  //return calculated checksum
  return checksum;
}

//Transmit payload data over Serial Comm port including checksum at the end
void TransmitPayloadOverSerial(En_DevDataType DataType) 
{
  String payloadData = "";

  if(DataType == EN_DEV_ATTR)
  {
    //Attributes: $SBDAT,0 (MachineType),3.35 (CalibFactor),16 (ThresholdWrapCount),86293 (TareOffset),A*13
    payloadData += PAYLOAD_BEGIN;
    payloadData += PAYLOAD_BEGIN_HDR_ATTR;
    payloadData += COMMA_SEPARATOR;
    
    payloadData += String(cnfgJsonData.MachineType);
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(cnfgJsonData.LoadCellCalibFactor);
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(cnfgJsonData.ThresholdWrapCount);
    payloadData += COMMA_SEPARATOR;

    payloadData += String(cnfgJsonData.TareOffsetVal);
    payloadData += COMMA_SEPARATOR;
  }
  else if(DataType == EN_DEV_ANL)
  {
    //Analytics: $SBDAN,50(CurBaleWeight),G,16 (CurBaleWrapCount),2 (TotalBaleCount),500 (TotalBaleWeight),G,27 (Moisture),%,17.123456 (Lat),°,72.123456 (Lon),°,1 (GpsHBSts),A*13
    payloadData += PAYLOAD_BEGIN;
    payloadData += PAYLOAD_BEGIN_HDR_ANL;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->CurrBaleWeight_grms, 2);
    payloadData += COMMA_SEPARATOR;
    payloadData += GRAMS;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->CurrBaleWrapCount);
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->TotBaleCount);
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->TotBaleWeight_grms, 2);
    payloadData += COMMA_SEPARATOR;
    payloadData += GRAMS;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->MoistureLevel);
    payloadData += COMMA_SEPARATOR;
    payloadData += MOISTURE_LEVEL_PERCENT;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->latitude, 6);
    payloadData += COMMA_SEPARATOR;
    payloadData += DEGREES;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->longitude, 6);
    payloadData += COMMA_SEPARATOR;
    payloadData += DEGREES;
    payloadData += COMMA_SEPARATOR;
  
    payloadData += String(ptrBalerPayload->GPSHeartBeatSts);
    payloadData += COMMA_SEPARATOR;
  }
  else
  {
    //
  }

  payloadData += DATA_VALID;
  payloadData += PAYLOAD_ASTERISK;
  payloadData += String(PayloadChecksumCalculate(payloadData), HEX);
  payloadData += PAYLOAD_END;

  Serial.print(payloadData);
}
