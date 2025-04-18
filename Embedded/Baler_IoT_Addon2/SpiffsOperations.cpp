#include "SpiffsOperations.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <FS.h>

ConfigJson_T cnfgJsonData = {0.0, EN_MACHINE_TYPE_UNDEFINED, 0, "", 0, 0, 0.0};

En_SpiffsOpStatus setUpAndGetDataFromSpiffs(void)
{
  En_SpiffsOpStatus status;

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]SPIFFS Mount Failed");
#endif
    /**************Display Info**************/
    status = EN_SPIFFS_MOUNT_FAILED;
    /**************Display Info**************/
  }

  //Check if config.json file exist or not
  if (SPIFFS.exists(CONFIG_FILE_PATH)) 
  {
#if ENABLE_DEBUG
    Serial.print("[INFO]");
    Serial.print(CONFIG_FILE_PATH);
    Serial.println(" File exists.");
#endif  
    //If file exists then read data from spiffs
    ReadDataFromSpiffs(&cnfgJsonData);
  }
  //NOTE: Need to decide that, if file doesn't exist then just display that info or
  //create config.json file and write with default data
  else 
  {
#if ENABLE_DEBUG
    //Serial.println("[INFO]File does not exist.");
    Serial.print("[INFO]");
    Serial.print(CONFIG_FILE_PATH);
    Serial.println(" File does not exists.");
#endif
    /**************Display Info**************/
    status = EN_FILE_DOESNOT_EXIST;
    /**************Display Info**************/

    //If file doesn't exist then create config.json and write with default data
    WriteDataToSpiffs(EN_UPDATE_DEFAULT_SPIFFS, &cnfgJsonData);
  }

  switch(cnfgJsonData.MachineType)
  {
    case EN_MACHINE_TYPE_ASB:
      //Machine type is ASB
      status = EN_VALID_MACHINE_TYPE;
      break;

    case EN_MACHINE_TYPE_MSB:
      //Machine type is MSB
      status = EN_VALID_MACHINE_TYPE;
      break;

    case EN_MACHINE_TYPE_UNDEFINED:
      //Machine type undefined
      status = EN_INVALID_MACHINE_TYPE;
      break;

    default:
      //Invalid machine type
      status = EN_INVALID_MACHINE_TYPE;
      break;
  }
  return status;
}

En_SpiffsOpStatus ReadDataFromSpiffs(ConfigJson_T *cnfgJsonDataSpiffs)
{
  En_SpiffsOpStatus status;

  //Get the JSON data back from spiffs
  File file = SPIFFS.open(CONFIG_FILE_PATH, FILE_READ);
  if (!file) 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]Failed to open file for reading");
#endif   
    /********Display Error**********/
    status = EN_FAILED_TO_OPEN_READ;
    /********Display Error**********/

    return status;
  }

  // Deserialize JSON from file
  StaticJsonDocument<MAX_SIZE_OF_CONFIG_JSON_FILE_BYTES> readDoc;
  DeserializationError error = deserializeJson(readDoc, file);
  if (error) 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]Failed to read file");
#endif
    /********Display Error**********/
    status = EN_FAILED_DESERIALZATION;
    /********Display Error**********/

    return status;
  }

  // Print the JSON data
  cnfgJsonDataSpiffs->MachineType = readDoc["machinetype"];
  cnfgJsonDataSpiffs->LoadCellCalibFactor = readDoc["loadcellcalib"];
  cnfgJsonDataSpiffs->ThresholdWrapCount = readDoc["wrapcount"];
  cnfgJsonDataSpiffs->TareOffsetVal = readDoc["tareoffset"];

  /**************************************************/
  //NOTE: If keys are not available then readDoc() will return 0
  /**************************************************/
#if ENABLE_DEBUG
  Serial.println("[INFO]Read JSON from file:");
  Serial.print("[INFO]machinetype: ");
  Serial.println(cnfgJsonDataSpiffs->MachineType);
  Serial.print("[INFO]loadcellcalib: ");
  Serial.println(cnfgJsonDataSpiffs->LoadCellCalibFactor);
  Serial.print("[INFO]wrapcount: ");
  Serial.println(cnfgJsonDataSpiffs->ThresholdWrapCount);
  Serial.print("[INFO]tareoffset: ");
  Serial.println(cnfgJsonDataSpiffs->TareOffsetVal);
#endif  
  file.close();

  return status;
}

En_SpiffsOpStatus WriteDataToSpiffs(En_SpiffsParamType ParamType, ConfigJson_T *cnfgJsonDataSpiffs)
{
  En_SpiffsOpStatus status;
  File file;
  DeserializationError error;
  // Create a JSON object to write
  StaticJsonDocument<MAX_SIZE_OF_CONFIG_JSON_FILE_BYTES> doc;
  //ConfigJson_T jsonSpiffsStruct = {0.0, EN_MACHINE_TYPE_UNDEFINED, 0};

  if(!(ParamType == EN_UPDATE_DEFAULT_SPIFFS))
  {
    //Get the JSON data back from spiffs
    file = SPIFFS.open(CONFIG_FILE_PATH, FILE_READ);
    if (!file) 
    {
#if ENABLE_DEBUG
    Serial.println("[INFO]Failed to open file for reading");
#endif   
      /********Display Error**********/
      status = EN_FAILED_TO_OPEN_READ;
      /********Display Error**********/

      return status;
    }

    error = deserializeJson(doc, file);
    if (error) 
    {
  #if ENABLE_DEBUG
      Serial.println("[INFO]Failed to read file");
  #endif
      /********Display Error**********/
      status = EN_FAILED_DESERIALZATION;
      /********Display Error**********/

      return status;
    }

    file.close();
  }

  //----------------------------------

  // Create config.json file and Write default data
  file = SPIFFS.open(CONFIG_FILE_PATH, FILE_WRITE);
  if (!file) 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]Failed to open file for writing");
#endif
    /*******Display Error*******/
    status = EN_FAILED_TO_OPEN_WRITE;
    /*******Display Error*******/

    return status;
  }
    // Create a JSON object to write
  //StaticJsonDocument<MAX_SIZE_OF_CONFIG_JSON_FILE_BYTES> doc;

  switch(ParamType)
  {
    case EN_MACHINE_TYPE_SPIFFS:
      doc["machinetype"]    = cnfgJsonDataSpiffs->MachineType;
      break;

    case EN_CALIB_FACTOR_SPIFFS:
      doc["loadcellcalib"] = cnfgJsonDataSpiffs->LoadCellCalibFactor;
      break;

    case EN_WRAP_COUNT_SPIFFS:
      doc["wrapcount"] = cnfgJsonDataSpiffs->ThresholdWrapCount;

    case EN_TARE_OFFSET_SPIFFS:
      doc["tareoffset"] = cnfgJsonDataSpiffs->TareOffsetVal;
      break;

    case EN_UPDATE_DEFAULT_SPIFFS:
      doc["machinetype"]    = cnfgJsonDataSpiffs->MachineType;
      doc["loadcellcalib"]  = cnfgJsonDataSpiffs->LoadCellCalibFactor;
      doc["wrapcount"]      = cnfgJsonDataSpiffs->ThresholdWrapCount;
      doc["tareoffset"]     = cnfgJsonDataSpiffs->TareOffsetVal;
      break;

    default:
#if ENABLE_DEBUG
      Serial.println("[INFO]Invalid");
#endif
      break;
  }

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) 
  {
#if ENABLE_DEBUG
    Serial.println("[INFO]Failed to write JSON to file");
#endif
    /*******Display Error*******/
    //What is the plan of action if write fails?
    status = EN_FAILED_TO_WRITE_JSON_TO_FILE;
    /*******Display Error*******/

    return status;
  }
  else 
  {
    /*******Display Info*******/
#if ENABLE_DEBUG
    Serial.println("[INFO]JSON data written to SPIFFS file successfully...!");
#endif
    /*******Display Info*******/
  }
  file.close();

  return status;
}

// En_SpiffsOpStatus WriteDataToSpiffs(En_SpiffsParamType ParamType, ConfigJson_T *cnfgJsonDataSpiffs)
// {
//   En_SpiffsOpStatus status;
//   //ConfigJson_T jsonSpiffsStruct = {0.0, EN_MACHINE_TYPE_UNDEFINED, 0};

//   //ReadDataFromSpiffs(&jsonSpiffsStruct);

//   // Create config.json file and Write default data
//   File file = SPIFFS.open(CONFIG_FILE_PATH, FILE_WRITE);
//   if (!file) 
//   {
// #if ENABLE_DEBUG
//     Serial.println("[INFO]Failed to open file for writing");
// #endif
//     /*******Display Error*******/
//     status = EN_FAILED_TO_OPEN_WRITE;
//     /*******Display Error*******/

//     return status;
//   }
//     // Create a JSON object to write
//   StaticJsonDocument<MAX_SIZE_OF_CONFIG_JSON_FILE_BYTES> doc;

//   switch(ParamType)
//   {
//     case EN_MACHINE_TYPE_SPIFFS:
//       doc["machinetype"]    = cnfgJsonDataSpiffs->MachineType;
//       // doc["loadcellcalib"]  = jsonSpiffsStruct.LoadCellCalibFactor;
//       // doc["wrapcount"]      = jsonSpiffsStruct.WrapCount;
//       break;

//     case EN_CALIB_FACTOR_SPIFFS:
//       doc["loadcellcalib"] = cnfgJsonDataSpiffs->LoadCellCalibFactor;
//       // doc["machinetype"] = jsonSpiffsStruct->MachineType;
//       // doc["wrapcount"] = jsonSpiffsStruct->WrapCount;
//       break;

//     case EN_WRAP_COUNT_SPIFFS:
//       doc["wrapcount"] = cnfgJsonDataSpiffs->WrapCount;
//       // doc["machinetype"] = jsonSpiffsStruct->MachineType;
//       // doc["loadcellcalib"] = jsonSpiffsStruct->LoadCellCalibFactor;
//       break;

//     case EN_UPDATE_ALL_SPIFFS:
//       doc["machinetype"] = cnfgJsonDataSpiffs->MachineType;
//       doc["loadcellcalib"] = cnfgJsonDataSpiffs->LoadCellCalibFactor;
//       doc["wrapcount"] = cnfgJsonDataSpiffs->WrapCount;
//       break;

//     default:
// #if ENABLE_DEBUG
//       Serial.println("[INFO]Invalid");
// #endif
//       break;
//   }

//   // Serialize JSON to file
//   if (serializeJson(doc, file) == 0) 
//   {
// #if ENABLE_DEBUG
//     Serial.println("[INFO]Failed to write JSON to file");
// #endif
//     /*******Display Error*******/
//     //What is the plan of action if write fails?
//     status = EN_FAILED_TO_WRITE_JSON_TO_FILE;
//     /*******Display Error*******/

//     return status;
//   }
//   else 
//   {
// #if ENABLE_DEBUG
//     Serial.println("[INFO]JSON data written to SPIFFS file successfully...!");
// #endif
//     /*******Display Info*******/

//     /*******Display Info*******/
//   }
//   file.close();

//   return status;
// }

En_BalerMachineType Get_MachineType(void)
{
  return cnfgJsonData.MachineType;
}

void Set_MachineType(En_BalerMachineType MachineType)
{
  cnfgJsonData.MachineType = MachineType;
}

float Get_LoadCellCalibFactor(void)
{
  return cnfgJsonData.LoadCellCalibFactor;
  //return 3.25;
}

void Set_LoadCellCalibFactor(float CalibFactorVal)
{
  cnfgJsonData.LoadCellCalibFactor = CalibFactorVal;
}
