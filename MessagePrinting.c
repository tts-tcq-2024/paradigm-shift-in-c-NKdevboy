
#include "MessagePrinting.h"

void PrintWaringMSGinterface(int WaringType , int CurrentBatteryPro)
{
	if((GetWaringMessage((CurrentBatteryPro),(WaringType-1))) != NULL)
	{
		printf("%s",GetWaringMessage((CurrentBatteryPro),(WaringType-1)));
	}
}


void PrintErrorMsg(int property)
{
	printf("%s",GetErrorMessage(property));
}