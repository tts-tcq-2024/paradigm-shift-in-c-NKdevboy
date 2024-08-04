#include "StandardMacro.h"

extern float MinValues[NOOFBATTERYPROPERTYCHECK];
extern float MaxValues[NOOFBATTERYPROPERTYCHECK];
extern unsigned char EarlyWarning[NOOFBATTERYPROPERTYCHECK];

// setting data 
#define SetEarlyWarningPer(index,value) (EarlyWarning[(index)]= (value))
#define SetMinValues(index,value) (MinValues[(index)]= (value))
#define SetMaxValues(index,value) (MaxValues[(index)]=(value))

// Setting specfic data 
//min
#define SetTempMinValue(value) (SetMinValues(TEMPERATURE,(value)))
#define SetSocpMinValue(value) (SetMinValues(SATEOFCHARGE,(value)))
#define SetChargeRateMinValue(value) (SetMinValues(CHARGERATE,(value)))

//max
#define SetTempMaxValue(value) (SetMaxValues(TEMPERATURE,(value)))
#define SetSocpMaxValue(value) (SetMaxValues(SATEOFCHARGE,(value)))
#define SetChargeRateMaxValue(value) (SetMaxValues(CHARGERATE,(value)))

// getting data
#define GetEarlyWarningPer(index) (EarlyWarning[(index)])
#define GetMinValues(index) (MinValues[(index)])
#define GetMaxValues(index) (MaxValues[(index)])

// getting specfic data 
//min
#define GetTempMinValue() (GetMinValues(TEMPERATURE))
#define GetSocpMinValue() (GetMinValues(SATEOFCHARGE))
#define GetChargeRateMinValue() (GetMinValues(CHARGERATE))

//max
#define GetTempMaxValue() (GetMaxValues(TEMPERATURE))
#define GetSocpMaxValue() (GetMaxValues(SATEOFCHARGE))
#define GetChargeRateMaxValue() (GetMaxValues(CHARGERATE))

