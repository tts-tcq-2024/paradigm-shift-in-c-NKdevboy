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

#define PASS 1
#define FAIL 0

#define LISTOFLANGUAGE 2

typedef enum
{
	ENGLISH,
	DEUTSCH
}ListOfLang;

typedef enum
{ 
	TEMPERATURE,
	SATEOFCHARGE,
	CHARGERATE
}ListOfProperties;


typedef int(*BatteryPropertiesChecks)(float);



int batteryIsOk(float Temperature, float Soc, float ChargeRate);
void CopyBatteryValueToLocalArr(float *arr,float Temperature, float Soc, float ChargeRate);
int batterychargeRateCheck(float ChargeRate);
int batterySocCheck(float Soc);
int batteryTempCheck(float Temperature);

float MinValues[NOOFBATTERYPROPERTYCHECK]={0};
float MaxValues[NOOFBATTERYPROPERTYCHECK]={0};
unsigned char EarlyWarning[NOOFBATTERYPROPERTYCHECK]={0};
ListOfLang CurrentLang ;

#define ListProperties \
{ \
	batteryTempCheck, \
	batterySocCheck, \
	batterychargeRateCheck, \
}


BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK] = ListProperties;

char * ListofErrorMsg[LISTOFLANGUAGE][NOOFBATTERYPROPERTYCHECK] = 
{
	{
		"Temperature out of range!\n",
		"State of Charge out of range!\n",
		"Charge Rate out of range!\n"
	},
	{
		"Temperatur außerhalb des Bereichs!\n"
		"Ladezustand außerhalb der Reichweite!\n"
		"Gebührensatz außerhalb des Bereichs!\n"
	}
};

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

// GET error message 
#define GetErrorMessage(value) ListofErrorMsg[(GetCurrentLanguage())][(value)]

unsigned char CheckSmallerValue(float value,float ref)
{
	if(value < ref)
	{
		return FAIL;
	}
	return PASS;
}

unsigned char CheckLargerValue(float value,float ref)
{
	if(value > ref)
	{
		return FAIL;
	}
	return PASS;
}

unsigned char CheckBothValues(float value,float SmallRef,float LargerRef)
{
	return ((CheckSmallerValue(value,SmallRef))&&(CheckLargerValue(value,LargerRef)));
}

void PrintErrorMsg(ListOfProperties property)
{
	printf("%s",GetErrorMessage(property));
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
	retval = CheckLargerValue(ChargeRate,GetChargeRateMaxValue());
	if(!retval)
	{
		PrintErrorMsg(CHARGERATE);
	}
	return retval;
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
  float ValueOfBatteryCheck[NOOFBATTERYPROPERTYCHECK]={0};
  
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
