#include <stdio.h>
#include <assert.h>

#define NOT_VALID 255

#define MIN_TEMP 0
#define MIN_SOC 20
#define MIN_CHAEGERATE NOT_VALID

#define MAX_TEMP 45
#define MAX_SOC 80
#define MAX_CHAEGERATE 0.8

#define NOOFBATTERYPROPERTYCHECK 3

typedef enum
{
	ENGLISH,
	DEUTSCH
}ListOfLang;

#define TEMPERATURE 0
#define SATEOFCHARGE 1
#define CHARGERATE 2


typedef int(*BatteryPropertiesChecks)(float);


int batteryIsOk(float Temperature, float Soc, float ChargeRate);
void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate);
int batterychargeRateCheck(float ChargeRate);
int batterySocCheck(float Soc);
int batteryTempCheck(float Temperature);

float MinValues[NOOFBATTERYPROPERTYCHECK]={0};
float MaxValues[NOOFBATTERYPROPERTYCHECK]={0};
unsigned char EarlyWarning[NOOFBATTERYPROPERTYCHECK]={0};
ListOfLang CurrentLang = ENGLISH;

#define ListProperties \
{ \
	batteryTempCheck, \
	batterySocCheck, \
	batterychargeRateCheck, \
}


BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK] = ListProperties;

// setting data 
#define SetCurrentLanguage(value) (CurrentLang = (value))
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
#define GetCurrentLanguage() (CurrentLang)
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


unsigned char CheckSmallerValue(float value,float ref)
{
	if(value < ref)
	{
		return 0;
	}
	return 1;
}

unsigned char CheckLargerValue(float value,float ref)
{
	if(value > ref)
	{
		return 0;
	}
	return 1;
}

int batteryTempCheck(float Temperature)
{
	if(((CheckSmallerValue(Temperature,GetTempMinValue()))&&(CheckLargerValue(Temperature,GetTempMaxValue()))))
	{
		return 1;
	}
	return 0;
}

int batterySocCheck(float Soc)
{
	if(((CheckSmallerValue(Soc,GetSocpMinValue()))&&(CheckLargerValue(Soc,GetSocpMaxValue()))))
	{
		return 1;
	}
	return 0;
}

int batterychargeRateCheck(float ChargeRate)
{
    if(CheckLargerValue(ChargeRate,GetChargeRateMaxValue()))
    {
        return 1;
    }
	return 0;
}

void init_call(void)
{

	SetCurrentLanguage(ENGLISH);

	SetTempMinValue(MIN_TEMP);
	SetSocpMinValue(MIN_SOC);
	SetChargeRateMinValue(MAX_CHAEGERATE);
	
	SetTempMaxValue(MAX_TEMP);
	SetSocpMaxValue(MAX_SOC);
	SetChargeRateMaxValue(MAX_CHAEGERATE);
	
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
  float ValueOfBatteryCheck[NOOFBATTERYPROPERTYCHECK]={0}
  
  CopyBatteryValueToLocalArr(ValueOfBatteryCheck,Temperature,Soc,ChargeRate);
  
  for(int Index = 0;Index < NOOFBATTERYPROPERTYCHECK;Index++ )
  {
	 returnVal &= ListOfPropertiesCheck[Index](ValueOfBatteryCheck[Index]);
  }

  return returnVal;
}

int main() {
  init_call();
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
