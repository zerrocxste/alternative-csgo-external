#include "process_find.h"

cProcessFind g_ProcessFind;

bool cProcessFind::InitProcess()
{
	if (this->FindProcessID() && this->FindProcessHandle())
		return true;

	return false;
}

bool cProcessFind::FindProcessID()
{
	HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProc == INVALID_HANDLE_VALUE)
	{
		this->dwProcessID = 0x0;
		return false;
	}

	PROCESSENTRY32 cmc32;

	cmc32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProc, &cmc32))
	{
		CloseHandle(hProc);
		this->dwProcessID = 0x0;
		return false;
	}

	do 
	{
		if (strcmp(cmc32.szExeFile, "csgo.exe") == 0)
		{
			CloseHandle(hProc);
			this->dwProcessID = cmc32.th32ProcessID;
			return true;
		}
	} 
	while (Process32Next(hProc, &cmc32));

	CloseHandle(hProc);

	return false;
}

bool cProcessFind::FindProcessHandle()
{
	this->hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);

	if (hProc == NULL)
		return false;
	else
		return true;
}
