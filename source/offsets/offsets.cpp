#include "offsets.h"
#include "../settings/settings.h"

#pragma warning (disable: 4244)

cOffsets g_Offsets;

void cOffsets::LoadOffsets()
{
	if (g_Settings.bFileExists("C://CSGOCheat//Offsets.ini"))
	{
		const char* SectionSig = "signatures";

		this->dwClientState = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwClientState", "0"));
		this->dwClientState_GetLocalPlayer = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwClientState_GetLocalPlayer", "0"));
		this->dwClientState_ViewAngles = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwClientState_ViewAngles", "0"));
		this->dwEntityList = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwEntityList", "0"));
		this->dwForceJump = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwForceJump", "0"));
		this->dwGameRulesProxy = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwGameRulesProxy", "0"));
		this->dwGlowObjectManager = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwGlowObjectManager", "0"));
		this->dwLocalPlayer = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "dwLocalPlayer", "0"));
		this->m_bDormant = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionSig, "m_bDormant", "0"));

		const char* SectionNetvar = "netvars";

		this->m_SurvivalGameRuleDecisionTypes = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_SurvivalGameRuleDecisionTypes", "0"));
		this->m_aimPunchAngle = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_aimPunchAngle", "0"));
		this->m_bIsScoped = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_bIsScoped", "0"));
		this->m_bSpottedByMask = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_bSpottedByMask", "0"));
		this->m_dwBoneMatrix = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_dwBoneMatrix", "0"));
		this->m_fFlags = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_fFlags", "0"));
		this->m_hActiveWeapon = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_hActiveWeapon", "0"));
		this->m_iCrosshairId = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iCrosshairId", "0"));
		this->m_iFOV = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iFOV", "0"));
		this->m_iGlowIndex = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iGlowIndex", "0"));
		this->m_iHealth = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iHealth", "0"));
		this->m_iItemDefinitionIndex = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iItemDefinitionIndex", "0"));
		this->m_iShotsFired = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iShotsFired", "0"));
		this->m_iTeamNum = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_iTeamNum", "0"));
		this->m_vecOrigin = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_vecOrigin", "0"));
		this->m_vecVelocity = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_vecVelocity", "0"));
		this->m_vecViewOffset = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_vecViewOffset", "0"));
		this->m_viewPunchAngle = atof(g_Settings.Read(g_Settings.OffsetsFile, SectionNetvar, "m_viewPunchAngle", "0"));
		
		std::cout << "offsets loaded" << std::endl;	
	}
	else
		std::cout << "offsets load error" << std::endl;
}