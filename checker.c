#include <stdio.h>
#include <assert.h>

#include "StandardMacro.h"
#include "TestCase.h"
#include "UserDefineDataTypes.h"
#include "MinMaxBatteryProperties.h"
#include "Language.h"

int batteryIsOk(float Temperature, float Soc, float ChargeRate);
void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate);
int batterychargeRateCheck(float ChargeRate);
int batterySocCheck(float Soc);
int batteryTempCheck(float Temperature);

int CurrentLang ;

#define ListProperties \
{ \
	batteryTempCheck, \
	batterySocCheck, \
	batterychargeRateCheck, \
}

BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK] = ListProperties;


unsigned char CheckValueLessThanRef(float value,float ref)
{
	if(value < ref)
	{
		return PASS;
	}
	return FAIL;
}

unsigned char CheckValueGreaterThanRef(float value,float ref)
{
	if(value > ref)
	{
		return PASS;
	}
	return FAIL;
}

unsigned char CheckBothValues(float value,float SmallRef,float LargerRef)
{
	return ((CheckValueLessThanRef(value,LargerRef))&&(CheckValueGreaterThanRef(value,SmallRef)));
}

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

void init_BatteryChecker(void)
{

	SetCurrentLanguage(ENGLISH);

	SetTempMinValue(MIN_TEMP);
	SetSocpMinValue(MIN_SOC);
	SetChargeRateMinValue(MAX_CHAEGERATE);
	
	SetTempMaxValue(MAX_TEMP);
	SetSocpMaxValue(MAX_SOC);
	SetChargeRateMaxValue(MAX_CHAEGERATE);
	SetEarlyWarningPer(TEMPERATURE,5);
	SetEarlyWarningPer(SATEOFCHARGE,5);
	SetEarlyWarningPer(CHARGERATE,5);
	
}

float CalculateWarningValue(unsigned char CurrentEarlyWar,int CurrentBatteryPro)
{
	return ((GetMaxValues(CurrentBatteryPro)*CurrentEarlyWar)/100);
}

int CheckEarlyWarninginterface(float LowerValue,float LargerValue , float CutValue ,int WarningType)
{
	if(CheckBothValues(CutValue,LowerValue,LargerValue))
	{
		return WarningType;
	}
	return 0;
}

void CheckEarlyWarning(float WarningValue,float ValueOfBatteyPro,int CurrentBatteryPro)
{
	int WaringType = 255;
	WaringType = CheckEarlyWarninginterface((GetMaxValues(CurrentBatteryPro)-WarningValue),(GetMaxValues(CurrentBatteryPro)),(ValueOfBatteyPro),HIGHType);
    WaringType |= CheckEarlyWarninginterface((GetMinValues(CurrentBatteryPro)),(GetMinValues(CurrentBatteryPro)+WarningValue),(ValueOfBatteyPro),LOWType);

	PrintWaringMSGinterface(WaringType,CurrentBatteryPro);
}

void CheckEarlyWarningMain(int CurrentBatteryPro,float ValueOfBatteyPro)
{
	float WarningValue =0;
	unsigned char CurrentEarlyWar = GetEarlyWarningPer(CurrentBatteryPro);
	if(EARLYWARNOTNEEDED != CurrentEarlyWar)
	{
		WarningValue = CalculateWarningValue(CurrentEarlyWar,CurrentBatteryPro);
		CheckEarlyWarning(WarningValue,ValueOfBatteyPro,CurrentBatteryPro);
	}
}

void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate)
{
	arr[0] = Temperature;
	arr[1] = Soc;
	arr[2] = ChargeRate;
}

int batteryIsOk(float Temperature, float Soc, float ChargeRate)
{
  int returnVal = 1;
  float ValueOfBatteryCheck[NOOFBATTERYPROPERTYCHECK]={0};
  
  CopyBatteryValueToLocalArr(ValueOfBatteryCheck,Temperature,Soc,ChargeRate);
  
  for(int Index = 0;Index < NOOFBATTERYPROPERTYCHECK;Index++ )
  {
	CheckEarlyWarningMain(Index,ValueOfBatteryCheck[Index]);
	returnVal &= ListOfPropertiesCheck[Index](ValueOfBatteryCheck[Index]);
  }

  return returnVal;
}


int main() {
 init_BatteryChecker();

TestCaseCaseTemperatureBelowLowerLimit();
TestCaseTemperatureAboveUpperLimit();
TestCaseSocBelowLowerLimit();
TestCaseSocAboveUpperLimit();
TestCaseChargeRateAboveUpperLimit();
TestCaseApproachingLowerTemperatureLimit();
TestCaseApproachingHigherTemperatureLimit();
TestCaseApproachingDischargeSOC();
TestCaseApproachingChargePeakSOC();
TestCaseApproachingMaxChargeRate();

}
