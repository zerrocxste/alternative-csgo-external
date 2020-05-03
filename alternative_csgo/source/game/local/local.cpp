#include "local.h"
#include "../../offsets/offsets.h"
#include "../../defines.h"
#include "../../memory_manager/memory_manager.h"

cLocal g_Local;

void cLocal::Update(DWORD clientAddress, DWORD engineAddres)
{
	this->dwLocalPlayer = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwLocalPlayer), this->dwLocalPlayer);

	this->dwGlowIndex = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwGlowObjectManager), this->dwGlowIndex);

	this->dwGameRulesProxy = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwGameRulesProxy), this->dwGameRulesProxy);

	this->iGameType = MemoryManager::Read<int>((this->dwGameRulesProxy + g_Offsets.m_SurvivalGameRuleDecisionTypes), this->iGameType);

	this->iTeam = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_iTeamNum), this->iTeam);

	this->iCrosshairId = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_iCrosshairId), this->iCrosshairId);

	this->iMoveFlag = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_fFlags), this->iMoveFlag);

	this->iShortFired = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_iShotsFired), this->iShortFired);

	this->iIsScoped = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_bIsScoped), this->iIsScoped);

	this->iFov = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_iFOV), this->iFov);

	this->vVelocity = MemoryManager::Read<Vector>((this->dwLocalPlayer + g_Offsets.m_vecVelocity), this->vVelocity);

	this->flVelocitySpeed = sqrt(POW(this->vVelocity.x) + POW(this->vVelocity.y));

	this->vViewOfs = MemoryManager::Read<Vector>((this->dwLocalPlayer + g_Offsets.m_vecOrigin), this->vViewOfs);

	this->vOrigin = MemoryManager::Read<Vector>((this->dwLocalPlayer + g_Offsets.m_vecViewOffset), this->vOrigin);

	this->vEye.x = this->vViewOfs.x + this->vOrigin.x;
	this->vEye.y = this->vViewOfs.y + this->vOrigin.y;
	this->vEye.z = this->vViewOfs.z + this->vOrigin.z;

	this->vPunchAngle = MemoryManager::Read<QAngle>((this->dwLocalPlayer + g_Offsets.m_aimPunchAngle), this->vPunchAngle);

	this->iCurWeapon = MemoryManager::Read<int>((this->dwLocalPlayer + g_Offsets.m_hActiveWeapon), this->iCurWeapon);
	this->iCurWeapon &= 0xFFF;

	this->dwWeaponEntity = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwEntityList + (this->iCurWeapon - 1) * 16), this->dwWeaponEntity);

	this->iWeaponIndex = MemoryManager::Read<int>((this->dwWeaponEntity + g_Offsets.m_iItemDefinitionIndex), this->iWeaponIndex);

	this->dwClientState = MemoryManager::Read<DWORD>((engineAddres + g_Offsets.dwClientState), this->dwClientState);

	this->dwLocalPlayerClientState = MemoryManager::Read<DWORD>((this->dwClientState + g_Offsets.dwClientState_GetLocalPlayer), this->dwLocalPlayerClientState);

	this->vViewAngle = MemoryManager::Read<QAngle>((this->dwClientState + g_Offsets.dwClientState_ViewAngles), this->vViewAngle);

	if (this->iWeaponIndex == 262148 || this->iWeaponIndex == 262205 || this->iWeaponIndex == 262176 || this->iWeaponIndex == 262146 || this->iWeaponIndex == 262180 
		|| this->iWeaponIndex == 262147 || this->iWeaponIndex == 262174 || this->iWeaponIndex == 262145 || this->iWeaponIndex == 262208 || this->iWeaponIndex == 262207
		|| this->iWeaponIndex == 262161 || this->iWeaponIndex == 262178 || this->iWeaponIndex == 262177 || this->iWeaponIndex == 262168 || this->iWeaponIndex == 262170
		|| this->iWeaponIndex == 262163 || this->iWeaponIndex == 262167 || this->iWeaponIndex == 262157 || this->iWeaponIndex == 262154 || this->iWeaponIndex == 262151
		|| this->iWeaponIndex == 262160 || this->iWeaponIndex == 262204 || this->iWeaponIndex == 262183 || this->iWeaponIndex == 262152 || this->iWeaponIndex == 262184
		|| this->iWeaponIndex == 262153 || this->iWeaponIndex == 262155 || this->iWeaponIndex == 262182 || this->iWeaponIndex == 262179 || this->iWeaponIndex == 262169
		|| this->iWeaponIndex == 262173 || this->iWeaponIndex == 262171 || this->iWeaponIndex == 262158 || this->iWeaponIndex == 262172)
	{//nekototie skins net zdes izza csgo update
		if (this->iWeaponIndex == 262151) { this->iCurSettingsWpn = WEAPON_AK47; }
		if (this->iWeaponIndex == 262204) { this->iCurSettingsWpn = WEAPON_M4A1S; }
		if (this->iWeaponIndex == 262160) { this->iCurSettingsWpn = WEAPON_M4A4; }
		if (this->iWeaponIndex == 262145) { this->iCurSettingsWpn = WEAPON_DEAGLE; }
		if (this->iWeaponIndex == 262148) { this->iCurSettingsWpn = WEAPON_GLOCK; }
		if (this->iWeaponIndex == 262205) { this->iCurSettingsWpn = WEAPON_USPS; }
		if (this->iWeaponIndex == 262176) { this->iCurSettingsWpn = WEAPON_P2000; }
		if (this->iWeaponIndex == 262153) { this->iCurSettingsWpn = WEAPON_AWP; }
		if (this->iWeaponIndex == 262184) { this->iCurSettingsWpn = WEAPON_SSG08; }
		if (this->iWeaponIndex == 262183) { this->iCurSettingsWpn = WEAPON_SG553; }
		if (this->iWeaponIndex == 262152) { this->iCurSettingsWpn = WEAPON_AUG; }
		if (this->iWeaponIndex == 262154) { this->iCurSettingsWpn = WEAPON_FAMAS; }
		if (this->iWeaponIndex == 262157) { this->iCurSettingsWpn = WEAPON_GALIL; }
		if (this->iWeaponIndex == 262146) { this->iCurSettingsWpn = WEAPON_DUALS; }
		if (this->iWeaponIndex == 262167) { this->iCurSettingsWpn = WEAPON_MP5SD; }
		if (this->iWeaponIndex == 262147) { this->iCurSettingsWpn = WEAPON_FIVE7; }
		if (this->iWeaponIndex == 262180) { this->iCurSettingsWpn = WEAPON_P250; }
		if (this->iWeaponIndex == 262174) { this->iCurSettingsWpn = WEAPON_TEC9; }
		if (this->iWeaponIndex == 262208) { this->iCurSettingsWpn = WEAPON_R8; }
		if (this->iWeaponIndex == 262207) { this->iCurSettingsWpn = WEAPON_CZ75; }
		if (this->iWeaponIndex == 262158) { this->iCurSettingsWpn = WEAPON_M249; }
		if (this->iWeaponIndex == 262172) { this->iCurSettingsWpn = WEAPON_NEGEV; }
		if (this->iWeaponIndex == 262155) { this->iCurSettingsWpn = WEAPON_G3SG1; }
		if (this->iWeaponIndex == 262182) { this->iCurSettingsWpn = WEAPON_SCAR20; }
		if (this->iWeaponIndex == 262161) { this->iCurSettingsWpn = WEAPON_MAC10; }
		if (this->iWeaponIndex == 262163) { this->iCurSettingsWpn = WEAPON_P90; }
		if (this->iWeaponIndex == 262168) { this->iCurSettingsWpn = WEAPON_UMP; }
		if (this->iWeaponIndex == 262170) { this->iCurSettingsWpn = WEAPON_BIZON; }
		if (this->iWeaponIndex == 262177) { this->iCurSettingsWpn = WEAPON_MP7; }
		if (this->iWeaponIndex == 262178) { this->iCurSettingsWpn = WEAPON_MP9; }
		if (this->iWeaponIndex == 262179) { this->iCurSettingsWpn = WEAPON_NOVA; }
		if (this->iWeaponIndex == 262179) { this->iCurSettingsWpn = WEAPON_XM; }
		if (this->iWeaponIndex == 262171) { this->iCurSettingsWpn = WEAPON_MAG7; }
		if (this->iWeaponIndex == 262173) { this->iCurSettingsWpn = WEAPON_SAWEDOFF; }
	}
	else
		this->iCurSettingsWpn = (this->iWeaponIndex > 0 && this->iWeaponIndex < 80) ? this->iWeaponIndex : 45;
}

bool cLocal::IsCurWeaponKnife(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_KNIFE:
	case WEAPON_KNIFE2:
	case WEAPON_KNIFE3:
	case WEAPON_BAREHANDS:
	case WEAPON_AXE:
	case WEAPON_HAMMER:
	case WEAPON_WRENCH:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponSniper(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_AWP:
	case WEAPON_SSG08:
	case WEAPON_SCAR20:
	case WEAPON_G3SG1:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponPistol(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_GLOCK:
	case WEAPON_USPS:
	case WEAPON_DUALS:
	case WEAPON_DEAGLE:
	case WEAPON_CZ75:
	case WEAPON_FIVE7:
	case WEAPON_P2000:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponRifle(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_M4A4:
	case WEAPON_M4A1S:
	case WEAPON_GALIL:
	case WEAPON_FAMAS:
	case WEAPON_AK47:
	case WEAPON_SG553:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponShotGun(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_XM:
	case WEAPON_MAG7:
	case WEAPON_SAWEDOFF:
	case WEAPON_NOVA:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponMachineGun(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_M249:
	case WEAPON_NEGEV:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponSubMachineGun(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_MP9:
	case WEAPON_P90:
	case WEAPON_MP7:
	case WEAPON_MAC10:
	case WEAPON_MP5SD:
	case WEAPON_UMP:
	case WEAPON_BIZON:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponNonAttack(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_HEGRENADE:
	case WEAPON_FLASHBANG:
	case WEAPON_DECOY:
	case WEAPON_SMOKE:
	case WEAPON_INCENDARY:
	case WEAPON_MOLOTOV:
	case WEAPON_BREACHCHARGE:
	case WEAPON_HAMMER:
	case WEAPON_TABLET:
	case WEAPON_TACTICALAWGRENADE:
	case WEAPON_FIREBOMB:
	case WEAPON_FRAGGRENADE:
	case WEAPON_BUMPMINE:
	case WEAPON_MEDISHOT:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponNade(void)
{
	switch (this->iWeaponIndex)
	{
	case WEAPON_HEGRENADE:
	case WEAPON_FLASHBANG:
	case WEAPON_DECOY:
	case WEAPON_SMOKE:
	case WEAPON_TACTICALAWGRENADE:
		return true;
	}

	return false;
}

bool cLocal::IsCurWeaponC4(void)
{
	if (this->iWeaponIndex == WEAPON_C4) return true;

	return false;
}

bool cLocal::IsCurWeaponGun(void)
{
	if (!IsCurWeaponNonAttack() && !IsCurWeaponKnife())
		return true;

	return false;
}