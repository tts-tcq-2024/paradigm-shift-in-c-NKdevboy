#include <stdio.h>
#include <assert.h>


int batteryTempCheck(float temperature)
{
    if(temperature < 0 || temperature > 45)
    {
        printf("Temperature out of range!\n");
        return 0;
    }
    else 
    {
        return 1;
    }
}

int batterySocCheck(float soc)
{
    if(soc < 20 || soc > 80)
    {
        printf("State of Charge out of range!\n");
        return 0;
     }
    else 
     {
        return 1;
     }
}

int batterychargeRateCheck(float chargeRate)
{
    if(chargeRate > 0.8) 
    {
        printf("Charge Rate out of range!\n");
        return 0;
    }
    else 
     {
        return 1;
     }
}

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
 // int returnVal = 1;
 // returnVal = batteryTempCheck(temperature);
 // returnVal = batterySocCheck(soc);
 // returnVal = batterychargeRateCheck(chargeRate);
 // return returnVal;
 return (batteryTempCheck(temperature) && batterySocCheck(soc) && batterychargeRateCheck(chargeRate) );
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
