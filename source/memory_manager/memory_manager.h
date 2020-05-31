#include "../alternative.h"
#include "../module_find/module_find.h"
#include "../process_find/process_find.h"

namespace MemoryManager
{
	template <class T>
	bool Write(DWORD address, T value)
	{
		return WriteProcessMemory(g_ProcessFind.GetProcessHandle(), (LPVOID)address, &value, sizeof(T), NULL);
	}
	template <class T>
	T Read(DWORD address, T addressValue)
	{
		T temp = addressValue;
		ReadProcessMemory(g_ProcessFind.GetProcessHandle(), (LPVOID)address, &temp, sizeof(temp), NULL);
		return temp;
	}
}

