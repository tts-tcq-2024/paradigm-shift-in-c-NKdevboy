#ifndef BatteryCheckes_H
#define BatteryCheckes_H
#include "BatteryCheckes.h"
#endif

#ifndef MessagePrinting_H
#define MessagePrinting_H
#include "MessagePrinting.h"
#endif


#ifndef MinMaxBatteryProperties_H
#define MinMaxBatteryProperties_H
#include "MinMaxBatteryProperties.h"
#endif


BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK] = ListProperties;

int batteryTempCheck(float Temperature)
{
	int retval = 255;
	retval = CheckBothValues(Temperature,GetTempMinValue(),GetTempMaxValue());
	if(!retval)
	{
		PrintErrorMsg(TEMPERATURE);
	}
	return retval;
}

int batterySocCheck(float Soc)
{
	int retval = 255;
	retval = CheckBothValues(Soc,GetSocpMinValue(),GetSocpMaxValue());
	if(!retval)
	{
		PrintErrorMsg(SATEOFCHARGE);
	}
	return retval;
}

int batterychargeRateCheck(float ChargeRate)
{
	int retval = 255;
	retval = CheckValueLessThanRef(ChargeRate,GetChargeRateMaxValue());
	if(!retval)
	{
		PrintErrorMsg(CHARGERATE);
	}
	return retval;
}