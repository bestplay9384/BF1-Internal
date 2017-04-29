#pragma once

#include "stdafx.h"

#define GXLPARAM(lp) ((short)LOWORD(lp))
#define GYLPARAM(lp) ((short)HIWORD(lp))


class IHooks
{
private:

	static HWND tWindow;

public:

	static BOOLEAN KeysPressed[256];

	static void Initialize(const wchar_t* Target);
	static void Restore();

	static void HooksInput();
};

