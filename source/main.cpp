#include <iostream>
#include <Windows.h>
#include <experimental/filesystem>
#include <urlmon.h>

#pragma comment (lib, "urlmon.lib")

#include "../resource/resource.h"

#include "alternative.h"
#include "cvars/cvars.h"
#include "settings/settings.h"
#include "gui/gui.h"
#include "wndproc.h"
#include "defines.h"
#include "module_find/module_find.h"
#include "offsets/offsets.h"
#include "helpers.h"

namespace fs = std::experimental::filesystem;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	helpers::window::RegMyWindowClass(hInstance, WindowName, IDI_ICON1);

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	int x = screen_rect.right / 2 - 280;
	int y = screen_rect.bottom / 2 - 175;

	HWND hWnd = CreateWindow(WindowName, WindowName, WS_POPUP, x, y, WindowSizeX + 16, WindowSizeY + 20
		, NULL, NULL, hInstance, NULL);
	//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

	if (!hWnd) 
		return 2;

	helpers::d3d::init(hWnd, hInstance);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	helpers::console::attach("info");

	gui.ImGuiInit(hWnd, g_pd3dDevice);

	cheat.InitHack();	

	URLDownloadToFile(0, "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.toml", "C://CSGOCheat//Offsets.ini", 0, 0);

	std::string IniPath(path);
	if (!fs::is_directory(IniPath))
		fs::create_directories(IniPath);

	strcpy(g_Settings.IniFile, g_Settings.SetConfigName(EMPTY_CFG));
	strcpy(g_Settings.OffsetsFile, "C:\\CSGOCheat\\Offsets.ini");

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		static bool bSetup = true;

		if (bSetup)
		{
			g_Cvars.Load();
			g_Offsets.LoadOffsets();

			bSetup = false;
		}

		auto& io = ImGui::GetIO();
		pos_mouse_t.x = io.MousePos.x;
		pos_mouse_t.y = io.MousePos.y;

		gui.GuiLoop();
		cheat.HackLoop();

		gui.Render(g_pd3dDevice, g_d3dpp);
	}

	gui.DestroyImgui();

	helpers::console::detach();

	helpers::d3d::destoy();

	DestroyWindow(hWnd);
	UnregisterClass(WindowName, hInstance);

	return 0;
}

