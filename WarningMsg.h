#include "StandardMacro.h"
#include "Language.h"

extern const char * ListofWarningMsg[LISTOFLANGUAGE][NOOFBATTERYPROPERTYCHECK][LISTOFWARNINGPERPROPERTIES];
// ENGLISH WARNING 
#define WarningForTEMPERATUREHighENG {"Warning: Approaching high temperature limit!\n"}
#define WarningForTEMPERATURELowENG  {"Warning: Approaching low temperature limit!\n"}

#define ListOfWarningForTEMPERATUREENG {WarningForTEMPERATURELowENG,WarningForTEMPERATUREHighENG}

#define WarningForSATEOFCHARGEHighENG {"Warning: Approaching high SOC limit!\n"}
#define WarningForSATEOFCHARGELowENG  {"Warning: Approaching low SOC limit!\n"}

#define ListOfWarningForSATEOFCHARGEENG {WarningForSATEOFCHARGELowENG,WarningForSATEOFCHARGEHighENG}

#define WarningForCHARGERATEHighENG {"Warning: Approaching high Charge rate limit!\n"}
#define WarningForCHARGERATELowENG  {NULL}

#define ListOfWarningForCHARGERATEENG {WarningForCHARGERATELowENG,WarningForCHARGERATEHighENG}

#define ALLENGLISHWARNING { \
	ListOfWarningForTEMPERATUREENG, \
	ListOfWarningForSATEOFCHARGEENG, \
	ListOfWarningForCHARGERATEENG, \
}
// GERMANY WARNING
#define WarningForTEMPERATUREHighGER {"Warnung: Annäherung an hohe Temperaturgrenze!\n"}
#define WarningForTEMPERATURELowGER  {"Warnung: Annäherung an niedrige Temperaturgrenze!\n"}

#define ListOfWarningForTEMPERATUREGER {WarningForTEMPERATURELowGER,WarningForTEMPERATUREHighGER}

#define WarningForSATEOFCHARGEHighGER {"Warnung: Annäherung an hohes SoC-Limit!\n"}
#define WarningForSATEOFCHARGELowGER  {"Warnung: Annäherung an niedrige SoC-Grenze!\n"}

#define ListOfWarningForSATEOFCHARGEGER {WarningForSATEOFCHARGELowGER,WarningForSATEOFCHARGEHighGER}

#define WarningForCHARGERATEHighGER {"Warnung: Annäherung an hohe Gebührenratenbegrenzung!\n"}
#define WarningForCHARGERATELowGER  {NULL}

#define ListOfWarningForCHARGERATEGER {WarningForCHARGERATELowGER,WarningForCHARGERATEHighGER}

#define ALLGERMANYWARNING { \
	ListOfWarningForTEMPERATUREGER, \
	ListOfWarningForSATEOFCHARGEGER, \
	ListOfWarningForCHARGERATEGER \
}

#define TOTALWARNINGS {ALLENGLISHWARNING,ALLGERMANYWARNING}

#define GetWaringMessage(CurrentPro,WaringType) ListofWarningMsg[(GetCurrentLanguage())][(CurrentPro)][(WaringType)]