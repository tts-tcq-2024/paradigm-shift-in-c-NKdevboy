#ifndef StandardMacro_H
#define StandardMacro_H
#include "StandardMacro.h"
#endif

#ifndef Language_H
#define Language_H
#include "Language.h"
#endif

#ifndef MinMaxBatteryProperties_H
#define MinMaxBatteryProperties_H
#include "MinMaxBatteryProperties.h"
#endif

#include "BatteryCheckerInit.h"

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