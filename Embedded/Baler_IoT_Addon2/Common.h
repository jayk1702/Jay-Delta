#define ENABLE_DEBUG                        1
#define ENABLE_SRL_CMD_DBG                  1
#define DEVICE_ACTIVE_DBG_STS_ENB           0
#define ENABLE_LCD 
#define GPS_ENABLE                          1

#define MAX_BALE_WRAP_COUNT                 16 //TODO: Count should be taken from the app

#define NUM_ZERO                            0
#define NUM_ONE                             1

#define NUM_OF_READINGS                     10

#define BALER_DEVICE_NAME                   "SBDT0001"
#define PAYLOAD_BEGIN_HDR_ANL               "SBDAN"
#define PAYLOAD_BEGIN_HDR_ATTR              "SBDAT"
#define GRAMS                               "G"  //GRMS - Grams
#define KILOGRAMS                           "Kg"
#define MOISTURE_LEVEL_PERCENT              "%"
#define COMMA_SEPARATOR                     ","
#define PAYLOAD_BEGIN                       "$"
#define PAYLOAD_ASTERISK                    "*"
#define PAYLOAD_END                         "\r\n"
#define DATA_VALID                          "A"
#define DEGREES                             "°" //press Win + R, type charmap, hit Enter and copy degrees

typedef enum 
{
  EN_MACHINE_TYPE_ASB = 0,
  EN_MACHINE_TYPE_MSB = 1,
  EN_MACHINE_TYPE_UNDEFINED = 255
}En_BalerMachineType;

typedef enum 
{
  EN_MACHINE_STATE_IDLE = 0,
  EN_MACHINE_STATE_FEEDING_STARTED=1,
  EN_MACHINE_STATE_FEEDING_COMPLETE=2,
  EN_MACHINE_STATE_VR_WRAP_SQUEEZ=3,
  EN_MACHINE_STATE_VR_WRAP_EXPAND=4,
  EN_MACHINE_STATE_CHAMBER_OPENED=5,
  EN_MACHINE_STATE_CHAMBER_CLOSED=6,
  EN_MACHINE_STATE_HR_WRAP_STARTED=7,
  EN_MACHINE_STATE_HR_WRAP_COMPLETED=8,
  EN_MACHINE_STATE_WRAP_CUT_UP=9,
  EN_MACHINE_STATE_WRAP_CUT_DOWN=10,
  EN_MACHINE_STATE_BALE_UNLOADING_DOWN=11,
  EN_MACHINE_STATE_BALE_LOADING_UP=12,
  EN_MACHINE_STATE_UNDEFINED = 255
}En_MachineStateEvent;

typedef enum 
{
  EN_MACHINE_EVNT_PROXIMITY_SNSR=0,
  EN_MACHINE_EVNT_HR_WRAP_STARTED=1,
  EN_MACHINE_EVNT_BALE_UNLOADING_DOWN=2,
  EN_MACHINE_EVNT_UNDEFINED = 255
}En_MachineEvent;

typedef enum 
{
  EN_OPMODE_AUTO = 0,
  EN_OPMODE_MANUAL = 1,
  EN_OPMODE_UNDEFINED = 255
}En_OperationMode;

typedef enum
{
  CMD_PRMPT_SRL=0,
  MAIN_MENU_OPT_SRL,
  MAIN_MENU_OPT_SEL_SRL,
  MACH_TYPE_SRL,
  WRAP_COUNT_SRL,
  OK_SRL,
  WEIGHT_SRL,
  UNDEFINED_SRL=255
}En_SerialCmd;

typedef enum
{
  EN_MACHINE_TYPE_SPIFFS=0,
  EN_CALIB_FACTOR_SPIFFS=1,
  EN_WRAP_COUNT_SPIFFS=2,
  EN_TARE_OFFSET_SPIFFS=3,
  EN_UPDATE_DEFAULT_SPIFFS=4,
  EN_INVALID_PARAM_SPIFFS=255
}En_SpiffsParamType;

typedef enum
{
  EN_VALID_MACHINE_TYPE=0,
  EN_INVALID_MACHINE_TYPE=1,
  EN_SPIFFS_MOUNT_FAILED=2,
  EN_FAILED_TO_OPEN_READ=3,
  EN_FAILED_DESERIALZATION=4,
  EN_FILE_DOESNOT_EXIST=5,
  EN_FAILED_TO_OPEN_WRITE=6,
  EN_FAILED_TO_WRITE_JSON_TO_FILE=7,
  EN_SPIFFS_UNDIFINED=255
}En_SpiffsOpStatus;

typedef enum
{
  EN_DEV_ATTR = 0,
  EN_DEV_ANL = 1,
  EN_DEV_UNDEFINED = 255
}En_DevDataType;

typedef enum 
{
  BALE_INFO_DEAULT = 0,
  BALE_INFO_WEIGHT = 1,
  BALE_INFO_COUNT = 2,
  BALE_INFO_MOISTURE = 3,
  BALE_INFO_ERROR = 4,
  BALE_INFO_ATTRIBUTES = 5,
  BALE_UNDEFINED = 255
}En_BaleInformation;

#pragma pack(1)
typedef struct
{
  double latitude;
  double longitude;
  float MoistureLevel;
  float CurrBaleWeight_grms;
  float TotBaleWeight_grms;
  unsigned short TotBaleCount;
  unsigned char CurrBaleWrapCount;
  bool GPSHeartBeatSts;
}BalerPayload_S;

#pragma pack(1)
typedef struct
{
  float LoadCellCalibFactor;
  En_BalerMachineType MachineType;
  unsigned char ThresholdWrapCount;
  String VIN;
  unsigned int BzrONTimeInterval;
  unsigned int WrapEventWaitTmIntrvl;
  long TareOffsetVal;
}ConfigJson_T;

typedef struct
{
  bool MachineEvntFlg;
  En_MachineEvent MachineEvent;
}MachineEvent_T;

extern En_BalerMachineType Get_MachineType(void);

extern float Get_LoadCellCalibFactor(void);

extern void HasTimerExpired(void);
extern void ProxSnsrEvntHndlr(void);
extern void UpdatePayloadDataAndTrnsmt(void);
extern void HndlBaleDataOnProxSnsrTmrExprd(void);
extern void TransmitPayloadOverSerial(En_DevDataType);
extern void SetMachineState(En_MachineStateEvent);
extern void StartTimer(En_MachineEvent);
extern void ResetTimerValue(En_MachineEvent);
extern void SetTare(void);
extern void Set_LoadCellCalibFactor(float);
extern void Set_MachineType(En_BalerMachineType);
extern void WrapCountLEDandBzrHndlr(void);
extern void fetchStableWeightAndTrnsmtPayload(void);
extern void powerUp_hx711(void);
extern void powerDown_hx711(void);
extern bool IsHx711PwrUp(void);
extern void MultiFuncLEDStateHndlr(void);
extern void WrapCountStsLEDandBzrHndlr(void);
extern void MultiFuncBtnHndlr(void);
extern void OnMultiFuncBtnShortPress(void);
extern void OnMultiFuncBtnLongPress(void);

extern En_SpiffsOpStatus WriteDataToSpiffs(En_SpiffsParamType, ConfigJson_T*);
extern void waitForUserCalibCmd(En_SerialCmd);
extern void SetScale(float);
extern double GetLatitude(void);
extern double GetLongitude(void);
extern bool GetGPSHeartBeatSts(void);
extern void turnOnRelay(void);
extern void ConfigRpiPowerRelayPins(void);
extern float Get_RoundOffWeight(float);
extern float CalculateCalibrationFactor(void);
extern float Get_WeightGrms(unsigned char);

extern void InitLCDModule(void);
extern void DisplayAnalytics(En_BaleInformation);