#pragma once

#include "../alternative.h"

class cSettings
{
public:
	char IniFile[MAX_PATH];
	char OffsetsFile[MAX_PATH];

	char * dtoa(char * s, double n);

	bool bFileExists(const char* cFileName);

	char * SetConfigName(const char * pszName);

	void Write(char * cFileName, const char * cSection, const char * cKey, char * cValue);
	char * Read(char *cFileName, const char *cSection, const char *cKey, const char *cDef);
};
extern cSettings g_Settings;
