#include <stdio.h>
#include <assert.h>


void batteryTempCheck(float temperature,int * out)
{
    if(temperature < 0 || temperature > 45)
    {
        printf("Temperature out of range!\n");
        *out &=0;
    }
}

void batterySocCheck(float soc,int * out)
{
    if(soc < 20 || soc > 80)
    {
        printf("State of Charge out of range!\n");
        *out &=0;
     }
}

void batterychargeRateCheck(float chargeRate,int * out)
{
    if(chargeRate > 0.8) 
    {
        printf("Charge Rate out of range!\n");
        *out &=0;
    }
}

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
  int returnVal = 1;
  batteryTempCheck(temperature,&returnVal);
  batterySocCheck(soc,&returnVal);
  batterychargeRateCheck(chargeRate,&returnVal);
  return returnVal;
 //return (batteryTempCheck(temperature) && batterySocCheck(soc) && batterychargeRateCheck(chargeRate) );
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
