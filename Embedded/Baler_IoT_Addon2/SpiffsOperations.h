#include "HW_Config.h"

#define CONFIG_FILE_PATH                    "/config.json"
#define MAX_SIZE_OF_CONFIG_JSON_FILE_BYTES  1024
#define FORMAT_SPIFFS_IF_FAILED             true

En_SpiffsOpStatus setUpAndGetDataFromSpiffs(void);
En_SpiffsOpStatus ReadDataFromSpiffs(ConfigJson_T*);
En_SpiffsOpStatus WriteDataToSpiffs(En_SpiffsParamType, ConfigJson_T*);

En_BalerMachineType Get_MachineType(void);

float Get_LoadCellCalibFactor(void);
void Set_LoadCellCalibFactor(float);
void Set_MachineType(En_BalerMachineType);