#pragma once

#include "../../alternative.h"

struct PlayersInfo
{
	DWORD dwEntity;
	DWORD dwBoneBase;
	DWORD dwGlowIndex;
	int iTeam;
	int iHealth;
	int iDormant;
	int iVisible;
	Vector vOrigin;
};

class cWorld
{
public:
	void Update(DWORD clientAddress);
	PlayersInfo players[32];
};
extern cWorld g_World;