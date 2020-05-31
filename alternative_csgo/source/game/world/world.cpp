#include "world.h"
#include "../../memory_manager/memory_manager.h"
#include "../../offsets/offsets.h"
#include "../../utils/utils.h"

cWorld g_World;

void cWorld::Update(DWORD clientAddress)
{
	for (int id = 1; id < 32; id++)
	{
		this->players[id].dwEntity = MemoryManager::Read<DWORD>((clientAddress + g_Offsets.dwEntityList + (id * 0x10)), this->players[id].dwEntity);
		this->players[id].dwBoneBase = MemoryManager::Read<DWORD>((this->players[id].dwEntity + g_Offsets.m_dwBoneMatrix), this->players[id].dwBoneBase);
		this->players[id].dwGlowIndex = MemoryManager::Read<DWORD>((this->players[id].dwEntity + g_Offsets.m_iGlowIndex), this->players[id].dwGlowIndex);
		this->players[id].iTeam = MemoryManager::Read<int>((this->players[id].dwEntity + g_Offsets.m_iTeamNum), this->players[id].iTeam);
		this->players[id].iHealth = MemoryManager::Read<int>((this->players[id].dwEntity + g_Offsets.m_iHealth), this->players[id].iHealth);
		this->players[id].iDormant = MemoryManager::Read<int>((this->players[id].dwEntity + g_Offsets.m_bDormant), this->players[id].iDormant);
		this->players[id].iVisible = g_Utils.bVisibilityCheck(this->players[id].dwEntity);
		this->players[id].vOrigin = MemoryManager::Read<Vector>((this->players[id].dwEntity + g_Offsets.m_vecOrigin), this->players[id].vOrigin);
	}
}