
#include "TestCase.h"
#include <assert.h>

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
   // assert(batteryIsOk(2, 55, 0.5));
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