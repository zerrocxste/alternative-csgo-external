#pragma once

#include "../alternative.h"
#include "../features/features.h"

class cUtils
{
public:
	void VectorAngles(const float * forward, float * angles);
	bool FovCheck(QAngle Target, float Fov);
	bool bVisibilityCheck(DWORD index);
	void RainbowColors(float colors[3]);
};
extern cUtils g_Utils;