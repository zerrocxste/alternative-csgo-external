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

namespace fs = std::experimental::filesystem;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
	WNDCLASS wcWindowClass = { 0 };
	wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
	wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	wcWindowClass.hInstance = hInst;
	wcWindowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcWindowClass.lpszClassName = lpzClassName;
	wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	return RegisterClass(&wcWindowClass);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!RegMyWindowClass(hInstance, WindowName))
		return 1;

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	int x = screen_rect.right / 2 - 280;
	int y = screen_rect.bottom / 2 - 175;

	HWND hWnd = CreateWindow(WindowName, WindowName, WS_POPUP, x, y, WindowSizeX + 16, WindowSizeY + 20
		, NULL, NULL, hInstance, NULL);
	//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

	if (!hWnd) 
		return 2;

	LPDIRECT3D9 pD3D;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		UnregisterClass(WindowName, hInstance);

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
	{
		pD3D->Release();
		UnregisterClass(WindowName, hInstance);
		return 0;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
		AllocConsole();
	}
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitle("info");
	SetWindowPos(GetConsoleWindow(), 0, 10, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	gui.ImGuiInit(hWnd, g_pd3dDevice);

	cheat.InitMemory();	

	URLDownloadToFile(0, "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.toml", "C://CSGOCheat//Offsets.ini", 0, 0);

	std::string IniPatch(path);
	if (!fs::is_directory(IniPatch))
		fs::create_directories(IniPatch);

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

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	gui.DestroyImgui();

	FreeConsole();

	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (pD3D) { pD3D->Release(); pD3D = NULL; }

	DestroyWindow(hWnd);
	UnregisterClass(WindowName, hInstance);

	return 0;
}

