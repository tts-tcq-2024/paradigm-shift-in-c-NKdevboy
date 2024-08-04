#ifndef StandardMacro_H
#define StandardMacro_H
#include "StandardMacro.h"
#endif

#ifndef UserDefineDataTypes_H
#define UserDefineDataTypes_H
#include "UserDefineDataTypes.h"
#endif

#ifndef MinMaxValueChecker_H
#define MinMaxValueChecker_H
#include "MinMaxValueChecker.h"
#endif

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