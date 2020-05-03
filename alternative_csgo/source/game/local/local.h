#pragma once

#include "../../alternative.h"
#include "../../math/math.h"

class cLocal
{
public:
	void Update(DWORD clientAddress, DWORD engineAddres);

	DWORD dwClientState;
	DWORD dwLocalPlayer;
	DWORD dwLocalPlayerClientState;
	DWORD dwGameRulesProxy;
	DWORD dwGlowIndex;
	DWORD dwWeaponEntity;
	//int WeaponAccountID;
	int iTeam;
	int iCrosshairId;
	int iMoveFlag;
	int iShortFired;
	int iIsScoped;
	int iFov;
	int iCurWeapon;
	int iWeaponIndex;
	int iGameType;
	//int bIsReload;
	int iCurSettingsWpn;
	//int iAccountId;
	float flVelocitySpeed;
	QAngle QViewAngle;
	Vector vViewOfs;
	Vector vOrigin;
	Vector vEye;
	Vector vPunchAngle;
	Vector vVelocity;

	bool IsCurWeaponKnife(void);
	bool IsCurWeaponSniper(void);
	bool IsCurWeaponPistol(void);
	bool IsCurWeaponRifle(void);
	bool IsCurWeaponShotGun(void);
	bool IsCurWeaponMachineGun(void);
	bool IsCurWeaponSubMachineGun(void);
	bool IsCurWeaponNonAttack(void);
	bool IsCurWeaponGun(void);
	bool IsCurWeaponNade(void);
	bool IsCurWeaponC4(void);
};
extern cLocal g_Local;

enum Weapon
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP = 24,
	WEAPON_XM = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_ZEUS = 31,
	WEAPON_P2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_BALLISTICSHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 41,
	WEAPON_KNIFE2 = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCENDARY = 48,
	WEAPON_C4 = 49,
	WEAPON_MEDISHOT = 57,
	WEAPON_KNIFE3 = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_R8 = 64,
	//
	WEAPON_TACTICALAWGRENADE = 68,
	WEAPON_BAREHANDS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_WRENCH = 78,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSIONDEVICE = 82,
	WEAPON_FRAGGRENADE = 83,
	WEAPON_BUMPMINE = 85,
};
