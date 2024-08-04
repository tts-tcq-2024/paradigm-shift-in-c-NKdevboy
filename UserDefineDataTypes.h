
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