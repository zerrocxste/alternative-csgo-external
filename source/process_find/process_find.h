#pragma once

#include "../alternative.h"

class cProcessFind
{
private:
	DWORD dwProcessID;
	HANDLE hProc;

	bool FindProcessHandle();
	bool FindProcessID();

public:
	bool InitProcess();

	int GetProcessID()
	{
		return this->dwProcessID;
	}

	HANDLE GetProcessHandle()
	{
		return this->hProc;
	}
};
extern cProcessFind g_ProcessFind;

