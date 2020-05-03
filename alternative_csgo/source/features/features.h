#pragma once

#include "../alternative.h"

class cFeatures
{
private:
	struct glow
	{
		float r; //0x4
		float g; //0x8
		float b; //0xc
		float a; //0x10
		char m_unk[4];
		float m_flUnk;
		float m_flBloomAmount;
		float m_flUnk1;
		bool m_bRenderWhenOccluded; //0x24
		bool m_bRenderWhenUnoccluded; //0x25
		bool m_bFullBloomRender; //0x26
		char m_unk1;
		int m_nFullBloomStencilTestValue;
		int m_nGlowStyle; //0x2c
		int m_nSplitScreenSlot;
		int m_nNextFreeSlot;
	} glow_t;

public:
	void GlowESP(DWORD clientAddress);
	void TriggerBot(DWORD clientAddress);
	void Bunnyhop(DWORD clientAddress);
	//void RCSStandalone(DWORD clientAddress);
	void RunAimbot(int bone, DWORD clientAddress);
	void Aimbot(DWORD clientAddress);
	//void FovChanger(DWORD clientAddress);
};
extern cFeatures g_Features;

