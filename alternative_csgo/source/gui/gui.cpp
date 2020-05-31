#include "gui.h"
#include "../cvars/cvars.h"
#include "../defines.h"

cGui gui;

struct fonts
{
	ImFont* title;
}font;

void cGui::ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	ImGui::CreateContext();

	auto io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.9f, NULL, io.Fonts->GetGlyphRangesCyrillic());

	font.title = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 26);

	ImGui_ImplWin32_Init(h);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(5, 3);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameRounding = 16.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.81f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.55f, 0.55f, 0.55f, 0.30f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.55f, 0.55f, 0.45f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.40f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 0.87f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.00f, 0.00f, 0.60f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.45f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void cGui::DestroyImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void cGui::Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

void cGui::Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
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
		Reset(g_pd3dDevice, g_d3dpp);
	}
}

void cGui::GuiLoop()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always, ImVec2(0.f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 16));

	ImVec2 vecPrevirousPos;

	int menur;
	menur = 1 * 255;

	static float Alpha = 0;
	static bool blyat = false;

	if (Alpha <= 0.95f && blyat == false)
	{
		Alpha += 0.005f;
		if (Alpha > 0.90f)
			blyat = true;
	}
	else
	{
		Alpha -= 0.005f;
		if (Alpha < 0.1f)
			blyat = false;
	}

	int a = (int)Alpha * 255;

	ImGuiWindowFlags WndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	ImGui::Begin(WindowName, nullptr, ImVec2(WindowSizeX + 16, 55), 1.0f, WndFlags);
	{
		vecPrevirousPos = ImGui::GetWindowPos();
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(vecPrevirousPos.x - 60, vecPrevirousPos.y), ImVec2(vecPrevirousPos.x + ImGui::GetWindowWidth(), vecPrevirousPos.y + 10),
			ImColor(menur, a, a, 255), ImColor(191, a, a, 255), ImColor(menur, 230 - a, 230 - a, 255), ImColor(menur, 230 - a, 230 - a, 255));
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 22);

		ImGui::PushFont(font.title);
		ImGui::Text("alternative");
		ImGui::PopFont();
	}
	ImGui::PopStyleVar();
	ImGui::End();

	ImGuiWindowFlags WndFlags1 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
	ImGui::SetNextWindowPos(ImVec2(vecPrevirousPos.x, vecPrevirousPos.y + 55), ImGuiCond_Always, ImVec2(0.f, 0.f));
	ImGui::Begin("2", nullptr, ImVec2(WindowSizeX + 16, 315), 1.0f, WndFlags1);
	{
		static int m_Page = 0;
		ImGui::BeginChild("1", ImVec2(170, 0), true);

		if (ImGui::Button("Aimbot", ImVec2(155, 20)))
			m_Page = 0;
		if (ImGui::Button("Triggerbot", ImVec2(155, 20)))
			m_Page = 1;
		if (ImGui::Button("Esp", ImVec2(155, 20)))
			m_Page = 2;
		if (ImGui::Button("Misc", ImVec2(155, 20)))
			m_Page = 3;
		if (ImGui::Button("Config", ImVec2(155, 20)))
			m_Page = 4;

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 148);
		if (ImGui::Button("Quit", ImVec2(155, 20)))
			ExitProcess(0);

		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("2", ImVec2(), true);

		static int cur_weapon_open = 1;
		int weapon_id = 1;

		if (cur_weapon_open == 0) { weapon_id = 0; }
		if (cur_weapon_open == 1) { weapon_id = WEAPON_AK47; }
		if (cur_weapon_open == 2) { weapon_id = WEAPON_M4A1S; }
		if (cur_weapon_open == 3) { weapon_id = WEAPON_M4A4; }
		if (cur_weapon_open == 4) { weapon_id = WEAPON_DEAGLE; }
		if (cur_weapon_open == 5) { weapon_id = WEAPON_GLOCK; }
		if (cur_weapon_open == 6) { weapon_id = WEAPON_USPS; }
		if (cur_weapon_open == 7) { weapon_id = WEAPON_P2000; }
		if (cur_weapon_open == 8) { weapon_id = WEAPON_AWP; }
		if (cur_weapon_open == 9) { weapon_id = WEAPON_SSG08; }
		if (cur_weapon_open == 10) { weapon_id = WEAPON_SG553; }
		if (cur_weapon_open == 11) { weapon_id = WEAPON_AUG; }
		if (cur_weapon_open == 12) { weapon_id = WEAPON_FAMAS; }
		if (cur_weapon_open == 13) { weapon_id = WEAPON_GALIL; }
		if (cur_weapon_open == 14) { weapon_id = WEAPON_DUALS; }
		if (cur_weapon_open == 15) { weapon_id = WEAPON_FIVE7; }
		if (cur_weapon_open == 16) { weapon_id = WEAPON_P250; }
		if (cur_weapon_open == 17) { weapon_id = WEAPON_TEC9; }
		if (cur_weapon_open == 18) { weapon_id = WEAPON_R8; }
		if (cur_weapon_open == 19) { weapon_id = WEAPON_CZ75; }
		if (cur_weapon_open == 20) { weapon_id = WEAPON_M249; }
		if (cur_weapon_open == 21) { weapon_id = WEAPON_NEGEV; }
		if (cur_weapon_open == 22) { weapon_id = WEAPON_G3SG1; }
		if (cur_weapon_open == 23) { weapon_id = WEAPON_SCAR20; }
		if (cur_weapon_open == 24) { weapon_id = WEAPON_MAC10; }
		if (cur_weapon_open == 25) { weapon_id = WEAPON_P90; }
		if (cur_weapon_open == 26) { weapon_id = WEAPON_UMP; }
		if (cur_weapon_open == 27) { weapon_id = WEAPON_BIZON; }
		if (cur_weapon_open == 28) { weapon_id = WEAPON_MP5SD; }
		if (cur_weapon_open == 29) { weapon_id = WEAPON_MP7; }
		if (cur_weapon_open == 30) { weapon_id = WEAPON_MP9; }
		if (cur_weapon_open == 31) { weapon_id = WEAPON_NOVA; }
		if (cur_weapon_open == 32) { weapon_id = WEAPON_XM; }
		if (cur_weapon_open == 33) { weapon_id = WEAPON_MAG7; }
		if (cur_weapon_open == 34) { weapon_id = WEAPON_SAWEDOFF; }

		const char* wpn_data[] = {
			"None","AK-47","M4A1S","M4A4","Deagle","Glock18","USP-S","P2000","AWP",
			"SSG-08","SSG553","AUG","Famas","Galil","Dual Berettas","Five-7","P250",
			"TEC9","R8","CZ75","M249","Negev","G3SG1", "SCAR20", "MAC10", "P90", "UMP",
			"Bizon", "MP5SD", "MP7", "MP9", "Nova", "XM", "MAG7", "Sawedoff"
		};

		const char* bone[] = { "Head", "Chest", "Stomach" };
		const char* bones[] = { "Head", "Chest", "Stomach", "All" };

		switch (m_Page)
		{
		case 0:
			ImGui::Text("Weapon:");
			ImGui::Combo("##weapons", &cur_weapon_open, wpn_data, IM_ARRAYSIZE(wpn_data));
			ImGui::Text("Aimbot");
			ImGui::Checkbox("Active##aimbot", &g_Cvars.WeaponNum[weapon_id].AimbotEnabled);
			ImGui::Checkbox("Teammates##aimbot", &g_Cvars.TeammatesEnabled);	
			ImGui::SliderFloat("Fov", &g_Cvars.WeaponNum[weapon_id].AimbotFov, 0.f, 60.f, "%.3f", 1.0f);
			ImGui::SliderFloat("Smooth", &g_Cvars.WeaponNum[weapon_id].AimbotSmooth, 0.f, 30.f, "%.3f", 1.0f); //+0.8f
			ImGui::SliderFloat("Recoil compensation y", &g_Cvars.WeaponNum[weapon_id].AimbotRecoilCompY, 0.f, 2.f, "%.3f", 1.0f);
			ImGui::SliderFloat("Recoil compensation x", &g_Cvars.WeaponNum[weapon_id].AimbotRecoilCompX, 0.f, 2.f, "%.3f", 1.0f);
			if ((weapon_id == 7) || (weapon_id == 60) || (weapon_id == 16) || (weapon_id == 39) || (weapon_id == 8) || (weapon_id == 10) || (weapon_id == 13) || (weapon_id == 13)
				|| (weapon_id == 14) || (weapon_id == 28) || (weapon_id == 23) || (weapon_id == 17) || (weapon_id == 19) || (weapon_id == 24) || (weapon_id == 26) || (weapon_id == 33) || (weapon_id == 34))
			{
				ImGui::SliderInt("Recoil compesation start", &g_Cvars.WeaponNum[weapon_id].AimbotRecoilCompStart, 0, 10, "%.3f");
				ImGui::SliderFloat("Recoil fov", &g_Cvars.WeaponNum[weapon_id].AimbotRecoilFov, 0.f, 60.f, "%.3f", 1.0f);
				ImGui::SliderFloat("Recoil smooth", &g_Cvars.WeaponNum[weapon_id].AimbotRecoilSmooth, 0.f, 30.f, "%.3f", 1.0f);
			}		
			ImGui::Combo("##AimbotBone", &g_Cvars.WeaponNum[weapon_id].AimbotBone, bone, IM_ARRAYSIZE(bone));
			break;
		case 1:
			ImGui::Text("Weapon:");
			ImGui::Combo("##weaponss", &cur_weapon_open, wpn_data, IM_ARRAYSIZE(wpn_data));
			ImGui::Text("Triggerbot");
			ImGui::Checkbox("Active##trigggers", &g_Cvars.WeaponNum[weapon_id].TriggerbotEnabled);
			ImGui::Checkbox("Teammates##aimbot", &g_Cvars.TeammatesEnabled);
			ImGui::SliderFloat("Fov##trigger", &g_Cvars.WeaponNum[weapon_id].TriggerbotFov, 0.001f, 1.0f, "%.3f", 1.0f);
			ImGui::Checkbox("Punchangle check", &g_Cvars.WeaponNum[weapon_id].TriggerbotPunchangleCheck);
			ImGui::SliderFloat("Max value punchangle", &g_Cvars.WeaponNum[weapon_id].TriggerbotMaxValuePunchangleCheck, 0.001f, 0.6f, "%.3f", 1.0f);
			if (cur_weapon_open == 8 || cur_weapon_open == 22 || cur_weapon_open == 23)
				ImGui::Checkbox("Only scoped", &g_Cvars.TriggerbotOnlyScoped);
			ImGui::Checkbox("Disable when walking ", &g_Cvars.WeaponNum[weapon_id].TriggerbotDisableWhenWalking);
			ImGui::Checkbox("Disable when jump ", &g_Cvars.WeaponNum[weapon_id].TriggerbotDisableWhenJump);
			ImGui::Combo("##TriggerBone", &g_Cvars.WeaponNum[weapon_id].TriggerbotBone, bones, IM_ARRAYSIZE(bones));
			break;
		case 2:
			ImGui::Text("Glow esp");
			ImGui::Checkbox("Active", &g_Cvars.ESPEnabled);
			ImGui::Checkbox("Teammates", &g_Cvars.GlowTeammates);
			ImGui::ColorEdit4("Color", g_Cvars.col, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview);
			break;
		case 3:
			ImGui::Text("Bunnyhop");
			ImGui::Checkbox("Active##bhop", &g_Cvars.BunnyhopEnabled);
			break;
		case 4:
			ImGui::Text("Config");
			if (ImGui::Button("Load", ImVec2{ 112, 25 }))
				g_Cvars.Load();
			ImGui::SameLine();
			if (ImGui::Button("Save", ImVec2{ 112, 25 }))
				g_Cvars.Save();
			ImGui::SameLine();
			if (ImGui::Button("Open config folder", ImVec2{ 112, 25 }))
				ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
			break;
		default:
			break;
		}

		ImGui::EndChild();
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowPos(ImVec2(vecPrevirousPos.x, vecPrevirousPos.y + 370), ImGuiCond_Always, ImVec2(0.f, 0.f));
		ImGui::Begin("3", nullptr, ImVec2(WindowSizeX + 16, 5), 1.0f, WndFlags1);
		{
			ImVec2 vec2CurrentPosition = ImGui::GetWindowPos();
			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(vec2CurrentPosition.x - 60, vec2CurrentPosition.y), ImVec2(vec2CurrentPosition.x + ImGui::GetWindowWidth(), vec2CurrentPosition.y + 11),
				ImColor(255, 127, 127, 255), ImColor(255, 127, 127, 255), ImColor(255, 127, 127, 255), ImColor(255, 127, 127, 255));
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
	ImGui::End();

	ImGui::EndFrame();
}