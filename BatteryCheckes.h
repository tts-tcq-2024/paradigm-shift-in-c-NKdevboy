#include "StandardMacro.h"
#include "UserDefineDataTypes.h"
#include "MinMaxValueChecker.h"

int batterychargeRateCheck(float ChargeRate);
int batterySocCheck(float Soc);
int batteryTempCheck(float Temperature);

extern BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK];

#define ListProperties \
{ \
	batteryTempCheck, \
	batterySocCheck, \
	batterychargeRateCheck, \
}