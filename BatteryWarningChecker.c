#ifndef BatteryWarningChecker_H
#define BatteryWarningChecker_H
#include "BatteryWarningChecker.h"
#endif

#ifndef MessagePrinting_H
#define MessagePrinting_H
#include "MessagePrinting.h"
#endif

float CalculateWarningValue(unsigned char CurrentEarlyWar,int CurrentBatteryPro);
int CheckEarlyWarninginterface(float LowerValue,float LargerValue , float CutValue ,int WarningType);
void CheckEarlyWarning(float WarningValue,float ValueOfBatteyPro,int CurrentBatteryPro);

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