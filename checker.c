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
#define EARLYWARNOTNEEDED NOT_VALID

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

#define LISTOFWARNINGPERPROPERTIES 2

#define ListProperties \
{ \
	batteryTempCheck, \
	batterySocCheck, \
	batterychargeRateCheck, \
}

#define ALL_ERROR_MSG {ENGLISH_ERROR_MSG,DEUTSCH_ERROR_MSG}

#define ENGLISH_ERROR_MSG \
{ \
"Temperature out of range!\n", \
"State of Charge out of range!\n", \
"Charge Rate out of range!\n" \
}

#define DEUTSCH_ERROR_MSG \
{ \
	"Temperatur außerhalb des Bereichs!\n" \
	"Ladezustand außerhalb der Reichweite!\n" \
	"Gebührensatz außerhalb des Bereichs!\n" \
}

// ENGLISH WARNING 
#define WarningForTEMPERATUREHighENG {"Warning: Approaching high temperature limit!\n"}
#define WarningForTEMPERATURELowENG  {"Warning: Approaching low temperature limit!\n"}

#define ListOfWarningForTEMPERATUREENG {WarningForTEMPERATURELowENG,WarningForTEMPERATUREHighENG}

#define WarningForSATEOFCHARGEHighENG {"Warning: Approaching high SOC limit!\n"}
#define WarningForSATEOFCHARGELowENG  {"Warning: Approaching low SOC limit!\n"}

#define ListOfWarningForSATEOFCHARGEENG {WarningForSATEOFCHARGELowENG,WarningForSATEOFCHARGEHighENG}

#define WarningForCHARGERATEHighENG {"Warning: Approaching high Charge rate limit!\n"}
#define WarningForCHARGERATELowENG  {NULL}

#define ListOfWarningForCHARGERATEENG {WarningForCHARGERATELowENG,WarningForCHARGERATEHighENG}

#define ALLENGLISHWARNING { \
	ListOfWarningForTEMPERATUREENG, \
	ListOfWarningForSATEOFCHARGEENG, \
	ListOfWarningForCHARGERATEENG, \
}
// GERMANY WARNING
#define WarningForTEMPERATUREHighGER {"Warnung: Annäherung an hohe Temperaturgrenze!\n"}
#define WarningForTEMPERATURELowGER  {"Warnung: Annäherung an niedrige Temperaturgrenze!\n"}

#define ListOfWarningForTEMPERATUREGER {WarningForTEMPERATURELowGER,WarningForTEMPERATUREHighGER}

#define WarningForSATEOFCHARGEHighGER {"Warnung: Annäherung an hohes SoC-Limit!\n"}
#define WarningForSATEOFCHARGELowGER  {"Warnung: Annäherung an niedrige SoC-Grenze!\n"}

#define ListOfWarningForSATEOFCHARGEGER {WarningForSATEOFCHARGELowGER,WarningForSATEOFCHARGEHighGER}

#define WarningForCHARGERATEHighGER {"Warnung: Annäherung an hohe Gebührenratenbegrenzung!\n"}
#define WarningForCHARGERATELowGER  {NULL}

#define ListOfWarningForCHARGERATEGER {WarningForCHARGERATELowGER,WarningForCHARGERATEHighGER}

#define ALLGERMANYWARNING { \
	ListOfWarningForTEMPERATUREGER, \
	ListOfWarningForSATEOFCHARGEGER, \
	ListOfWarningForCHARGERATEGER, \
}

#define TOTALWARNINGS {ALLENGLISHWARNING,ALLGERMANYWARNING}

BatteryPropertiesChecks ListOfPropertiesCheck[NOOFBATTERYPROPERTYCHECK] = ListProperties;

const char * ListofErrorMsg[LISTOFLANGUAGE][NOOFBATTERYPROPERTYCHECK] = ALL_ERROR_MSG;

const char * ListofWarningMsg[LISTOFLANGUAGE][NOOFBATTERYPROPERTYCHECK][LISTOFWARNINGPERPROPERTIES] = TOTALWARNINGS;



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

#define GetWaringMessage(CurrentPro,WaringType) ListofWarningMsg[(GetCurrentLanguage())][(CurrentPro)][(WaringType)]

#define LOWType 1
#define HIGHType 2

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
	retval = CheckValueLessThanRef(ChargeRate,GetChargeRateMaxValue());
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

void PrintWaringMSGinterface(int WaringType , int CurrentBatteryPro)
{
	if((GetWaringMessage((CurrentBatteryPro),(WaringType-1))) != NULL)
	{
		printf("%s",GetWaringMessage((CurrentBatteryPro),(WaringType-1)));
	}
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



void TestCaseCaseTemperatureBelowLowerLimit(void) 
{
    assert(!batteryIsOk(-10, 65, 0.5));
}

void TestCaseTemperatureAboveUpperLimit(void) 
{
    assert(!batteryIsOk(55, 65, 0.5));
}

void TestCaseSocBelowLowerLimit(void) 
{
    assert(!batteryIsOk(25, 10, 0.5));
}

void TestCaseSocAboveUpperLimit(void) 
{
    assert(!batteryIsOk(25, 91, 0.5));
}

void TestCaseChargeRateAboveUpperLimit(void) 
{
    assert(!batteryIsOk(25, 55, 1.0));
}

void TestCaseApproachingLowerTemperatureLimit(void) 
{
    assert(batteryIsOk(2, 55, 0.5));
}

void TestCaseApproachingHigherTemperatureLimit(void)
{
    assert(batteryIsOk(43, 55, 0.5));
}

void TestCaseApproachingDischargeSOC(void) 
{
    assert(batteryIsOk(35, 22, 0.5));
}

void TestCaseApproachingChargePeakSOC(void) 
{
    assert(batteryIsOk(35, 78, 0.5));
}

void TestCaseApproachingMaxChargeRate(void) 
{
    assert(batteryIsOk(20, 40, 0.77));
}


int main() {
  init_call();

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
