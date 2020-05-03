#include "alternative.h"
#include "cvars/cvars.h"
#include "utils/utils.h"

cCheat cheat;

void cCheat::InitMemory()
{
	if (g_ProcessFind.InitProcess())
	{
		std::cout << "process found. id: " << g_ProcessFind.GetProcessID() << ", handle: " << g_ProcessFind.GetProcessHandle() << std::endl;
		g_ModuleFind.InitModule();
	}
	else
		std::cout << "process not found" << std::endl;
}

void cCheat::HackLoop()
{
	if (FindGameWindow()) {
		if (GetTickCount() - this->dwExitTimers > 7000) 
			this->FirstLoad = true;
	}
	else {
		this->dwExitTimers = GetTickCount();
	}

	g_World.Update(g_ModuleFind.GetClientAddress());

	g_Local.Update(g_ModuleFind.GetClientAddress(), g_ModuleFind.GetEngineAddress());

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotEnabled)
		g_Features.Aimbot(g_ModuleFind.GetClientAddress());

	if (g_Cvars.ESPEnabled)
		g_Features.GlowESP(g_ModuleFind.GetClientAddress());

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotEnabled && !GetAsyncKeyState(VK_LBUTTON))
		g_Features.TriggerBot(g_ModuleFind.GetClientAddress());

	if (g_Cvars.BunnyhopEnabled)
		g_Features.Bunnyhop(g_ModuleFind.GetClientAddress());

	//if (g_Cvars.ESPColorRainbow)
	//	g_Utils.RainbowColors(g_Cvars.col);

	if (!FindGameWindow() && this->FirstLoad)
		exit(EXIT_SUCCESS);
}

bool cCheat::FindGameWindow()
{
	if (FindWindow(NULL, "Counter-Strike: Global Offensive") == NULL)
		return false;
	else
		return true;
}

