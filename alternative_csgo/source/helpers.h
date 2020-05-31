#pragma once

namespace helpers
{
	class console
	{
	public:
		static void attach(LPCSTR pszConsoleName)
		{
			if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
				AllocConsole();
			}
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			SetConsoleTitle(pszConsoleName);
			SetWindowPos(GetConsoleWindow(), 0, 10, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		static void detach()
		{
			FreeConsole();
		}
	};

	class window
	{
	public:
		static ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName, const int pIcon)
		{
			WNDCLASS wcWindowClass = { 0 };
			wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
			wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
			wcWindowClass.hInstance = hInst;
			wcWindowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(pIcon));
			wcWindowClass.lpszClassName = lpzClassName;
			wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
			return RegisterClass(&wcWindowClass);
		}
	};

	LPDIRECT3D9 pD3D;

	class d3d
	{
	public:
		static void init(HWND h, HINSTANCE hInstance)
		{
			if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
				UnregisterClass(WindowName, hInstance);

			ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
			g_d3dpp.Windowed = TRUE;
			g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
			g_d3dpp.EnableAutoDepthStencil = TRUE;
			g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
			g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

			if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, h, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
			{
				pD3D->Release();
				UnregisterClass(WindowName, hInstance);
			}
		}

		static void destoy()
		{
			if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
			if (pD3D) { pD3D->Release(); pD3D = NULL; }
		}
	};
}
