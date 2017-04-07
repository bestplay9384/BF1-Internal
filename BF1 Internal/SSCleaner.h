#pragma once

#include "stdafx.h"

using BitBlt_t = BOOL(__stdcall*)(HDC, int, int, int, int, HDC, int, int, DWORD);
using CopyResource_t = void(__stdcall*)(ID3D11DeviceContext*, ID3D11Resource*, ID3D11Resource*);
using CopySubresourceRegion_t = void(__stdcall*)(ID3D11DeviceContext*, ID3D11Resource*, unsigned int, unsigned int, unsigned int, unsigned int, ID3D11Resource*, unsigned int, const D3D11_BOX*);

class CSSCleaner
{
public:

	//HOOKS
	PLH::VEHHook* BitBltHook;
	PLH::VEHHook* CopyResourceHook;
	PLH::VEHHook* CopySubresourceHook;
	BitBlt_t oBitBlt;
	CopyResource_t oCopyResource;
	CopySubresourceRegion_t oCopySubresource;

	//DATA
	INT LastSSTick;
	INT CurrentSSTick;
	ID3D11Texture2D* CleanSS = nullptr;

	bool BitBltState = false;
	bool CopyResourceState = false;
	bool CopySubresourceRegionState = false;
	bool NeedSS = false;

	//FUNCTIONS
	bool HookBitBlt();
	bool HookCopyResource();
	bool HookCopySubresourceRegion();
	void TakeSS();
	ID3D11Texture2D* GetCleanSS() { return CleanSS; }
};


extern std::unique_ptr<CSSCleaner> SSCleaner;
