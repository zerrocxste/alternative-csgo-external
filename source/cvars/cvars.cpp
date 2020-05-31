#include "cvars.h"
#include "../settings/settings.h"

#pragma warning (disable: 4244) 

cCvars g_Cvars;

const char *szWeapons[] = {
	"unknown", "deagle", "duals", "five7", "glock", "", "", "ak47", "aug", "awp", "famas", "g3sg1", "" ,"galil", "m249", "", "m4a4",
	"mac10", "", "p90", "", "", "", "mp5sd", "ump", "xm", "bizon", "mag7", "negev", "sawedoff", "tec9", "", "p2000", "mp7", "mp9", "nova", "p250",
	"", "scar20", "ssg553", "ssg08", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "m4a1s", "usps", "", "cz75", "r8",
};

void cCvars::Load()
{
	if (!g_Settings.bFileExists(g_Settings.IniFile))
		return;

	const char *Section = "Settings";

	g_Cvars.ESPEnabled = atoi(g_Settings.Read(g_Settings.IniFile, Section, "GlowEspEnabled", "0"));
	g_Cvars.GlowTeammates = atoi(g_Settings.Read(g_Settings.IniFile, Section, "GlowTeammates", "0"));

	g_Cvars.col[0] = atof(g_Settings.Read(g_Settings.IniFile, Section, "Color_r", "0"));
	g_Cvars.col[1] = atof(g_Settings.Read(g_Settings.IniFile, Section, "Color_g", "0"));
	g_Cvars.col[2] = atof(g_Settings.Read(g_Settings.IniFile, Section, "Color_b", "0"));
	g_Cvars.col[3] = atof(g_Settings.Read(g_Settings.IniFile, Section, "Color_a", "0"));

	g_Cvars.ESPColorRainbow = atoi(g_Settings.Read(g_Settings.IniFile, Section, "RainbowColors", "0"));

	g_Cvars.BunnyhopEnabled = atoi(g_Settings.Read(g_Settings.IniFile, Section, "BunnyhopEnabled", "0"));

	g_Cvars.TeammatesEnabled = atoi(g_Settings.Read(g_Settings.IniFile, Section, "LegitbotTeammates", "0"));

	g_Cvars.TriggerbotOnlyScoped = atoi(g_Settings.Read(g_Settings.IniFile, Section, "TriggerbotOnlyScoped", "0"));

	for (int i = 0; i <= 64; i++)
	{
		if (i == 5 || i == 6 || i == 12 || i == 15 || i == 18 || i == 20 || i == 21 || i == 22 || i == 31 || i == 37
			|| i == 41 || i == 42 || i == 43 || i == 44 || i == 45 || i == 46 || i == 47 || i == 48 || i == 49
			|| i == 50 || i == 51 || i == 52 || i == 53 || i == 54 || i == 55 || i == 56 || i == 57 || i == 58
			|| i == 59 || i == 62)
			continue;

		const char *szNonRead = szWeapons[i];

		if (szNonRead != "unknown")
		{
			g_Cvars.WeaponNum[i].AimbotEnabled = atoi(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotEnabled", "0"));
			g_Cvars.WeaponNum[i].AimbotFov = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotFov", "0"));
			g_Cvars.WeaponNum[i].AimbotSmooth = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotSmooth", "0"));
			g_Cvars.WeaponNum[i].AimbotRecoilCompX = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompX", "0"));
			g_Cvars.WeaponNum[i].AimbotRecoilCompY = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompY", "0"));
			g_Cvars.WeaponNum[i].AimbotRecoilCompStart = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompStart", "0"));
			g_Cvars.WeaponNum[i].AimbotRecoilFov = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotRecoilFov", "0"));
			g_Cvars.WeaponNum[i].AimbotRecoilSmooth = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotRecoilSmooth", "0"));
			g_Cvars.WeaponNum[i].AimbotBone = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "AimbotBone", "0"));
			g_Cvars.WeaponNum[i].TriggerbotEnabled = atoi(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotEnabled", "0"));
			g_Cvars.WeaponNum[i].TriggerbotFov = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotFov", "0"));
			g_Cvars.WeaponNum[i].TriggerbotPunchangleCheck = atoi(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotPunchangleCheck", "0"));
			g_Cvars.WeaponNum[i].TriggerbotMaxValuePunchangleCheck = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotMaxValuePunchangleCheck", "0"));
			g_Cvars.WeaponNum[i].TriggerbotDisableWhenJump = atoi(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotDisableWhenJump", "0"));
			g_Cvars.WeaponNum[i].TriggerbotDisableWhenWalking = atoi(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotDisableWhenWalking", "0"));
			g_Cvars.WeaponNum[i].TriggerbotBone = atof(g_Settings.Read(g_Settings.IniFile, szWeapons[i], "TriggerbotBone", "0"));
		}
	}

	std::cout << "settings loaded" << std::endl;
}

void cCvars::Save()
{
	const char *Section = "Settings";
	char s[32];

	g_Settings.Write(g_Settings.IniFile, Section, "GlowEspEnabled", g_Settings.dtoa(s, g_Cvars.ESPEnabled));
	g_Settings.Write(g_Settings.IniFile, Section, "GlowTeammates", g_Settings.dtoa(s, g_Cvars.GlowTeammates));

	g_Settings.Write(g_Settings.IniFile, Section, "Color_r", g_Settings.dtoa(s, g_Cvars.col[0]));
	g_Settings.Write(g_Settings.IniFile, Section, "Color_g", g_Settings.dtoa(s, g_Cvars.col[1]));
	g_Settings.Write(g_Settings.IniFile, Section, "Color_b", g_Settings.dtoa(s, g_Cvars.col[2]));
	g_Settings.Write(g_Settings.IniFile, Section, "Color_a", g_Settings.dtoa(s, g_Cvars.col[3]));

	g_Settings.Write(g_Settings.IniFile, Section, "RainbowColors", g_Settings.dtoa(s, g_Cvars.ESPColorRainbow));

	g_Settings.Write(g_Settings.IniFile, Section, "BunnyhopEnabled", g_Settings.dtoa(s, g_Cvars.BunnyhopEnabled));

	g_Settings.Write(g_Settings.IniFile, Section, "LegitbotTeammates", g_Settings.dtoa(s, g_Cvars.TeammatesEnabled));

	g_Settings.Write(g_Settings.IniFile, Section, "TriggerbotOnlyScoped", g_Settings.dtoa(s, g_Cvars.TriggerbotOnlyScoped));

	for (int i = 0; i <= 64; i++)
	{
		if (i == 5 || i == 6 || i == 12 || i == 15 || i == 18 || i == 20 || i == 21 || i == 22 || i == 31 || i == 37
			|| i == 41 || i == 42 || i == 43 || i == 44 || i == 45 || i == 46 || i == 47 || i == 48 || i == 49
			|| i == 50 || i == 51 || i == 52 || i == 53 || i == 54 || i == 55 || i == 56 || i == 57 || i == 58
			|| i == 59 || i == 62)
			continue;

		const char *szNonWrite = szWeapons[i];

		if (szNonWrite != "unknown")
		{
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotEnabled", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotEnabled));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotFov", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotFov));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotSmooth", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotSmooth));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompX", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotRecoilCompX));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompY", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotRecoilCompY));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotRecoilCompStart", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotRecoilCompStart));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotRecoilFov", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotRecoilFov));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotRecoilSmooth", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotRecoilSmooth));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "AimbotBone", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].AimbotBone));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotEnabled", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotEnabled));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotFov", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotFov));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotPunchangleCheck", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotPunchangleCheck));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotMaxValuePunchangleCheck", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotMaxValuePunchangleCheck));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotDisableWhenJump", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotDisableWhenJump));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotDisableWhenWalking", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotDisableWhenWalking));
			g_Settings.Write(g_Settings.IniFile, szWeapons[i], "TriggerbotBone", g_Settings.dtoa(s, g_Cvars.WeaponNum[i].TriggerbotBone));
		}
	}

	std::cout << "settings saved" << std::endl;
}