#include "stdafx.h"

LRESULT __stdcall HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WNDPROC OldWndProc = nullptr;

HWND IHooks::tWindow = nullptr;
BOOLEAN IHooks::KeysPressed[256] = { FALSE };

void IHooks::Initialize(const wchar_t* Target)
{
	tWindow = FindWindow(0, Target);
	if (tWindow) OldWndProc = (WNDPROC)SetWindowLongPtr(tWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
}
	
void IHooks::Restore()
{
	SetWindowLongPtr(tWindow, GWLP_WNDPROC, (LONG_PTR)OldWndProc);
}


LRESULT __stdcall HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1.0f : -1.0f;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	case WM_KEYDOWN:
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		break;
	case WM_KEYUP:
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		break;
	}

	return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
	/*if (!Features::ShowMenu)
	{
		if (io.MouseDrawCursor)
			io.MouseDrawCursor = false;
		return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
	}
	else
	{
		if (!io.MouseDrawCursor)
			io.MouseDrawCursor = true;
		if (uMsg == WM_MOUSEMOVE || uMsg == WM_NCHITTEST || uMsg == WM_SETCURSOR)
			return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
	}*/
}
