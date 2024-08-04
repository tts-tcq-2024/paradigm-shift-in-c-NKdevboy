
#ifndef StandardMacro_H
#define StandardMacro_H
#include "StandardMacro.h"
#endif

#include "TestCase.h"

#ifndef UserDefineDataTypes_H
#define UserDefineDataTypes_H
#include "UserDefineDataTypes.h"
#endif

#include "MinMaxBatteryProperties.h"
#include "BatteryCheckes.h"
#include "BatteryWarningChecker.h"
#include "BatteryCheckerInit.h"

int batteryIsOk(float Temperature, float Soc, float ChargeRate);
void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate);
int CurrentLang =0;


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
//TestCaseApproachingHigherTemperatureLimit();
//TestCaseApproachingDischargeSOC();
//TestCaseApproachingChargePeakSOC();
//TestCaseApproachingMaxChargeRate();

}
