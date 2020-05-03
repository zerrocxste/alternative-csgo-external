#include "features.h"
#include "../offsets/offsets.h"
#include "../cvars/cvars.h"
#include "../memory_manager/memory_manager.h"
#include "../utils/utils.h"
#include "../defines.h"
#include "../module_find/module_find.h"
#include "../process_find/process_find.h"

#pragma warning (disable: 4244) 

cFeatures g_Features;

void cFeatures::GlowESP(DWORD clientAddress)
{
	for (int id = 0; id < 32; id++)
	{
		if (g_World.players[id].iHealth <= 0)
			continue;

		if (!g_Cvars.GlowTeammates && g_World.players[id].iTeam == g_Local.iTeam)
			continue;

		glow_t = MemoryManager::Read<glow>(g_Local.dwGlowIndex + (g_World.players[id].dwGlowIndex * 0x38) + 0x4, glow_t);

		glow_t.r = g_Cvars.col[0];
		glow_t.g = g_Cvars.col[1];
		glow_t.b = g_Cvars.col[2];
		glow_t.a = g_Cvars.col[3];
		glow_t.m_bRenderWhenOccluded = true;
		glow_t.m_bRenderWhenUnoccluded = false;

		MemoryManager::Write<glow>((g_Local.dwGlowIndex + (g_World.players[id].dwGlowIndex * 0x38) + 0x4), glow_t);
	}
}

void cFeatures::TriggerBot(DWORD clientAddress)
{
	std::deque<int> bone;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotBone == 0)
		bone.push_back(8);
	else if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotBone == 1)
		bone.push_back(6);
	else if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotBone == 2)
		bone.push_back(0);

	DWORD dwEntity = NULL; dwEntity = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwEntityList + (g_Local.iCrosshairId - 1) * 0x10), dwEntity);
	DWORD dwBoneBase = NULL; dwBoneBase = MemoryManager::Read<DWORD>((dwEntity + g_Offsets.m_dwBoneMatrix), dwBoneBase);
	int iHealth = NULL; iHealth = MemoryManager::Read<int>((dwEntity + g_Offsets.m_iHealth), iHealth);
	int iTeam = NULL; iTeam = MemoryManager::Read<int>((dwEntity + g_Offsets.m_iTeamNum), iTeam);

	QAngle QTarget;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotBone != 3)
	{
		Vector vBone;
		for (auto &&CurrentBone : bone)
		{
			vBone.x = MemoryManager::Read<float>((dwBoneBase + 0x30 * CurrentBone + 0x0C), vBone.x);
			vBone.y = MemoryManager::Read<float>((dwBoneBase + 0x30 * CurrentBone + 0x1C), vBone.y);
			vBone.z = MemoryManager::Read<float>((dwBoneBase + 0x30 * CurrentBone + 0x2C), vBone.z);
		}

		g_Utils.VectorAngles(vBone - g_Local.vEye, QTarget);
		QTarget.Normalize();
	}

	if (g_Cvars.TriggerbotOnlyScoped && g_Local.IsCurWeaponSniper() && g_Local.iIsScoped != 1)
		return;

	float flFov = g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotFov;

	if (iHealth == 0)
		return;	

	if (iTeam <= 1)
		return;

	if (g_Cvars.TeammatesEnabled && iTeam == g_Local.iTeam)
		return;

	if (g_Local.iCrosshairId <= 0 || g_Local.iCrosshairId >= 65)
		return;	

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotPunchangleCheck && 
		g_Local.vPunchAngle.x <= -(g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotMaxValuePunchangleCheck))
		return;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotDisableWhenWalking &&
		g_Local.flVelocitySpeed > 20)
		return;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotDisableWhenJump &&
		g_Local.iMoveFlag == 256)
		return;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].TriggerbotBone == 0 &&
		!((g_Local.QViewAngle.x - QTarget.x) <= 0.3 && (g_Local.QViewAngle.x - QTarget.x) >= -flFov
		&& (g_Local.QViewAngle.y - QTarget.y) <= flFov && (g_Local.QViewAngle.y - QTarget.y) >= -flFov))
		return;

	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
}

void cFeatures::Bunnyhop(DWORD clientAddress)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		auto pressed = (g_Local.iMoveFlag == 257) || (g_Local.iMoveFlag == 263) ? 5 : 4;
		MemoryManager::Write<int>(clientAddress + g_Offsets.dwForceJump, pressed);
	}
}

inline void SmoothAimAngles(const QAngle& MyViewAngles, const QAngle& AimAngles, QAngle& OutAngles, const float& Smoothing)
{
	OutAngles = AimAngles - MyViewAngles;

	OutAngles.Normalize();

	OutAngles[0] = OutAngles.x / Smoothing + MyViewAngles.x;
	OutAngles[1] = OutAngles.y / Smoothing + MyViewAngles.y;

	OutAngles.Normalize();
}

void cFeatures::RunAimbot(int bone, DWORD clientAddress)
{
	float flFOV;
	float flSmooth;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompStart > 0)
	{
		flFOV = g_Local.iShortFired >= g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompStart ? 
			g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilFov : g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotFov;

		flSmooth = g_Local.iShortFired >= g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompStart ? 30.8f - g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilSmooth
			: 30.8f - g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotSmooth;
	}
	else
	{
		flFOV = g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotFov;
		flSmooth = 30.8f - g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotSmooth;
	}

	float flRecoilCompX = g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompX;
	float flRecoilCompY = g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompY;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompStart > 0 && g_Local.iShortFired <= g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotRecoilCompStart)
	{
		flRecoilCompX = 0;
		flRecoilCompY = 0;
	}

	int m_iTarget = 0;

	float delta = FLT_MAX;

	for (int id = 1; id <= 32; id++)
	{
		if (g_World.players[id].iDormant != 0)
			continue;

		if (g_World.players[id].iHealth <= 0)
			continue;

		if (!g_Cvars.TeammatesEnabled && g_World.players[id].iTeam == g_Local.iTeam)
			continue;	

		if (g_Local.iGameType != 4 && g_World.players[id].iVisible == 0)
			continue;

		QAngle QTarget;
		g_Utils.VectorAngles(g_World.players[id].vOrigin - g_Local.vEye, QTarget);
		QTarget.Normalize();

		float flAngleDist = abs(g_Local.QViewAngle.y - QTarget.y);

		if (g_Utils.FovCheck(QTarget, flFOV) && flAngleDist < delta)
		{
			delta = flAngleDist;
			m_iTarget = id;
		}
	}

	if (m_iTarget == 0)
		return;

	Vector vBone;
	vBone.x = MemoryManager::Read<float>((g_World.players[m_iTarget].dwBoneBase + 0x30 * bone + 0x0C), vBone.x);
	vBone.y = MemoryManager::Read<float>((g_World.players[m_iTarget].dwBoneBase + 0x30 * bone + 0x1C), vBone.y);
	vBone.z = MemoryManager::Read<float>((g_World.players[m_iTarget].dwBoneBase + 0x30 * bone + 0x2C), vBone.z);

	QAngle QAimAngle, QSmoothedAimAngle;

	g_Utils.VectorAngles(vBone - g_Local.vEye, QAimAngle);
	QAimAngle.Normalize();

	QAimAngle.x -= g_Local.vPunchAngle.x * flRecoilCompY;
	QAimAngle.y -= g_Local.vPunchAngle.y * flRecoilCompX;
	QAimAngle.z = 0.f;
	
	SmoothAimAngles(g_Local.QViewAngle, QAimAngle, QSmoothedAimAngle, flSmooth);

	MemoryManager::Write<float>((g_Local.dwClientState + g_Offsets.dwClientState_ViewAngles), QSmoothedAimAngle.x);
	MemoryManager::Write<float>((g_Local.dwClientState + g_Offsets.dwClientState_ViewAngles + 0x4), QSmoothedAimAngle.y);
}

void cFeatures::Aimbot(DWORD clientAddress)
{
	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotSmooth == 0 || !g_Local.IsCurWeaponGun())
		return;

	std::deque<int> bone;

	if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotBone == 0)
		bone.push_back(8);
	else if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotBone == 1)
		bone.push_back(6);
	else if (g_Cvars.WeaponNum[g_Local.iCurSettingsWpn].AimbotBone == 2)
		bone.push_back(0);


	if (GetAsyncKeyState(VK_LBUTTON))
	{
		for (auto&& CurrentBone : bone)
		{
			RunAimbot(CurrentBone, clientAddress);
		}
	}
}

/*void cFeatures::FovChanger(DWORD clientAddress)
{
	if (g_Cvars.CustomFov > 0 && g_Local.bIsScoped != 1)
	{
		MemoryManager::Write<int>(ProcessFinder->GetProcessHandle(), (g_Local.dwLocalPlayer + g_Offsets.m_iFOV), g_Cvars.CustomFov);
	}
	else
	{
		MemoryManager::Write<int>(ProcessFinder->GetProcessHandle(), (g_Local.dwLocalPlayer + g_Offsets.m_iFOV), g_Local.iFov);
	}
}*/
