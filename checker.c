#include <stdio.h>
#include <assert.h>

#include "StandardMacro.h"
#include "TestCase.h"
#include "UserDefineDataTypes.h"
#include "MinMaxBatteryProperties.h"
#include "Language.h"
#include "BatteryCheckes.h"
#include "BatteryWarningChecker.h"

int batteryIsOk(float Temperature, float Soc, float ChargeRate);
void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate);

int CurrentLang ;

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
