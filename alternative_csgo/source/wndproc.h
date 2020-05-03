#pragma once

#include "gui/gui.h"

static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

POINT g_ptMousePos;
static bool g_bIsMouseCaptured = false;

struct pos_mouse
{
	float x, y;
}; 
pos_mouse pos_mouse_t;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ImGui_ImplDX9_InvalidateDeviceObjects();
			HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
	{
		if (g_bIsMouseCaptured)
		{
			RECT rc;
			POINT ptCursor;
			POINT ptDelta;

			GetWindowRect(hWnd, &rc);
			GetCursorPos(&ptCursor);
			ptDelta.x = g_ptMousePos.x - ptCursor.x;
			ptDelta.y = g_ptMousePos.y - ptCursor.y;

			MoveWindow(hWnd, rc.left - ptDelta.x, rc.top - ptDelta.y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
			g_ptMousePos.x = ptCursor.x;
			g_ptMousePos.y = ptCursor.y;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (!g_bIsMouseCaptured && pos_mouse_t.x > 0 && pos_mouse_t.y > 0 && pos_mouse_t.x < 675 && pos_mouse_t.y < 55)
		{
			SetCapture(hWnd);
			g_bIsMouseCaptured = true;
			GetCursorPos(&g_ptMousePos);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		if (g_bIsMouseCaptured)
		{
			ReleaseCapture();
			g_bIsMouseCaptured = false;
		}
		break;
	}
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}