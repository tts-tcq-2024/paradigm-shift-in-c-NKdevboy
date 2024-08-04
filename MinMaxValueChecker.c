#ifndef MinMaxValueChecker_H
#define MinMaxValueChecker_H
#include "MinMaxValueChecker.h"
#endif

#ifndef StandardMacro_H
#define StandardMacro_H
#include "StandardMacro.h"
#endif

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