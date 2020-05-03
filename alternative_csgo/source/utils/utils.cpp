#include "utils.h"
#include "../offsets/offsets.h"
#include "../memory_manager/memory_manager.h"

cUtils g_Utils;

void cUtils::VectorAngles(const float *forward, float *angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / 3.14f);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / 3.14f);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

bool cUtils::FovCheck(QAngle Target, float Fov)
{
	return ((g_Local.QViewAngle.x - Target.x) <= Fov && (g_Local.QViewAngle.x - Target.x) >= -Fov
		&& (g_Local.QViewAngle.y - Target.y) <= Fov && (g_Local.QViewAngle.y - Target.y) >= -Fov);
}

bool cUtils::bVisibilityCheck(DWORD index)
{
	int iMask = NULL;
	iMask = MemoryManager::Read<int>((index + g_Offsets.m_bSpottedByMask), iMask);

	return (iMask & (1 << (g_Local.dwLocalPlayerClientState))) != 0;
}

void cUtils::RainbowColors(float colors[3])
{
	static int counter = 0;

	if (colors[counter] >= 1.0f)
	{
		colors[counter] = 1.0f;
		counter += 1;

		if (counter > 2)
			counter = 0;
	}
	else
	{
		int prev = counter - 1;

		if (prev < 0)
			prev = 2;

		const float speed = 0.003f;
		colors[prev] -= speed;
		colors[counter] += speed;
	}
}

