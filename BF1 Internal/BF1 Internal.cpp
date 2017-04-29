#include "stdafx.h"

HMODULE mod;

void Init()
{
	static bool dbg = false;
	if (dbg)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	std::string ModTest = "Do you still see this string or are you blind...?";

	SSCleaner.reset(new CSSCleaner());
	Log.reset(new CLog());
	DX11.reset(new DX11Renderer());
	DX11->InitDevice(mod, L"Battlefield™ 1");

	if (dbg)
		ShowWindow(GetConsoleWindow(), SW_HIDE);

	FreeLibraryAndExitThread(mod, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		mod = hModule;

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AimbotThread, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



