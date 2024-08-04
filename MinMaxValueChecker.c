#include "MinMaxValueChecker.h"

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