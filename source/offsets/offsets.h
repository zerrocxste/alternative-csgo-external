#pragma once

#include "../alternative.h"

class cOffsets
{
public:
	ptrdiff_t m_SurvivalGameRuleDecisionTypes;
	ptrdiff_t m_aimPunchAngle;
	ptrdiff_t m_bIsScoped;
	ptrdiff_t m_bSpottedByMask;
	ptrdiff_t m_dwBoneMatrix;
	ptrdiff_t m_fFlags;
	ptrdiff_t m_hActiveWeapon;
	ptrdiff_t m_iCrosshairId;
	ptrdiff_t m_iFOV;
	ptrdiff_t m_iGlowIndex;
	ptrdiff_t m_iHealth;
	ptrdiff_t m_iItemDefinitionIndex;
	ptrdiff_t m_iShotsFired;
	ptrdiff_t m_iTeamNum;
	ptrdiff_t m_vecOrigin;
	ptrdiff_t m_vecVelocity;
	ptrdiff_t m_vecViewOffset;
	ptrdiff_t m_viewPunchAngle;

	ptrdiff_t dwClientState;
	ptrdiff_t dwClientState_ViewAngles;
	ptrdiff_t dwClientState_GetLocalPlayer;
	ptrdiff_t dwEntityList;
	ptrdiff_t dwForceJump;
	ptrdiff_t dwGameRulesProxy;
	ptrdiff_t dwGlowObjectManager;
	ptrdiff_t dwLocalPlayer;
	ptrdiff_t m_bDormant;

	void LoadOffsets();
};
extern cOffsets g_Offsets;


