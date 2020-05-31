#include "module_find.h"
#include "../process_find/process_find.h"
#include "../utils/utils.h"
#include "../offsets/offsets.h"
#include "../settings/settings.h"

cModuleFind g_ModuleFind;

bool cModuleFind::FindModule(const char* moduleName, MODULEENTRY32& module_base)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, g_ProcessFind.GetProcessID());

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hSnap);
		return false;
	}

	MODULEENTRY32 cmc32;

	cmc32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hSnap, &cmc32))
	{
		CloseHandle(hSnap);
		return false;
	}

	do
	{
		if (strcmp(cmc32.szModule, moduleName) == 0)
		{
			CloseHandle(hSnap);
			CopyMemory(&module_base, &cmc32, sizeof(MODULEENTRY32));
			return true;
		}
		Sleep(10);
	}
	while (Module32Next(hSnap, &cmc32));

	CloseHandle(hSnap);
}

bool cModuleFind::FindClientModule()
{
	static bool ret = this->FindModule("client_panorama.dll", this->modules_t.client);

	ret ? std::cout << "client_panorama.dll found. address: " << (PVOID)(DWORD)this->modules_t.client.modBaseAddr << std::endl :
		std::cout << "client_panorama.dll not found" << std::endl;

	return ret;
}

bool cModuleFind::FindEngineModule()
{
	static bool ret = this->FindModule("engine.dll", this->modules_t.engine);

	ret ? std::cout << "engine.dll found. address: " << (PVOID)(DWORD)this->modules_t.engine.modBaseAddr << std::endl :
		std::cout << "engine.dll not found" << std::endl;

	return ret;
}

bool cModuleFind::InitModule()
{
	if (!this->FindClientModule())
		return false;

	if (!this->FindEngineModule())
		return false;
}


