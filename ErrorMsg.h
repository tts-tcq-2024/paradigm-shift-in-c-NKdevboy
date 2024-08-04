#ifndef StandardMacro_H
#define StandardMacro_H
#include "StandardMacro.h"
#endif

#ifndef Language_H
#define Language_H
#include "Language.h"
#endif

extern const char * ListofErrorMsg[LISTOFLANGUAGE][NOOFBATTERYPROPERTYCHECK];

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

#define ALL_ERROR_MSG {ENGLISH_ERROR_MSG,DEUTSCH_ERROR_MSG}

// GET error message 
#define GetErrorMessage(value) ListofErrorMsg[(GetCurrentLanguage())][(value)]