#pragma once

#include "../alternative.h"

struct weapon
{
	bool AimbotEnabled;
	float AimbotFov;
	float AimbotSmooth;
	float AimbotRecoilCompX;
	float AimbotRecoilCompY;
	int AimbotRecoilCompStart;
	float AimbotRecoilFov;
	float AimbotRecoilSmooth;
	int AimbotBone;

	bool TriggerbotEnabled;
	int TriggerbotBone;
	float TriggerbotFov;
	bool TriggerbotPunchangleCheck;
	float TriggerbotMaxValuePunchangleCheck;
	bool TriggerbotDisableWhenJump;
	bool TriggerbotDisableWhenWalking;
};

class cCvars
{
private:
public:
	bool ESPEnabled = false;
	bool GlowTeammates = false;
	float col[4];
	bool ESPColorRainbow = false;

	int CustomFov = 0;

	bool BunnyhopEnabled = false;

	bool TeammatesEnabled = false;

	bool TriggerbotOnlyScoped = false;

	weapon WeaponNum[65];

	void Load();
	void Save();
};
extern cCvars g_Cvars;

