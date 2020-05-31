#pragma once

#include <Windows.h>
#include <corecrt_io.h>
#include <TlHelp32.h>
#include <deque>
#include <float.h>
#include <iostream>

#include "process_find/process_find.h"
#include "module_find/module_find.h"
#include "features/features.h"
#include "game/local/local.h"
#include "math/math.h"
#include "game/world/world.h"

class cCheat
{
private:
	bool FirstLoad = false;

	DWORD dwExitTimers;
public:
	bool FindGameWindow();
	void InitHack();
	void HackLoop();
};
extern cCheat cheat;




