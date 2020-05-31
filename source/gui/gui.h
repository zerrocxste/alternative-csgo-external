#pragma once

#include "../alternative.h"
#include "../features/features.h"

#include <d3d9.h>
#include <tchar.h>
#include <dinput.h>
#include "Dwmapi.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imgui_impl_win32.h"

class cGui
{
private:
	int x1, y1;
public:
	void ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice);
	void DestroyImgui();
	void Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp);
	void Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp);
	void GuiLoop();
	void setPos(int x, int y) { x1 = x, y1 = y; }
};
extern cGui gui;