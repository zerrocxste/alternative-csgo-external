#pragma once

#include "../alternative.h"

class cModuleFind
{
private:
	bool FindModule(const char* moduleName, MODULEENTRY32& module_base);
	bool FindClientModule();
	bool FindEngineModule();

	struct modules
	{
		MODULEENTRY32 client, engine;
	} modules_t;

public:
	bool InitModule();

	DWORD GetClientAddress()
	{
		return (DWORD)modules_t.client.modBaseAddr;
	}

	DWORD GetEngineAddress()
	{
		return (DWORD)modules_t.engine.modBaseAddr;
	}

	void auto_offsets();
};
extern cModuleFind g_ModuleFind;

