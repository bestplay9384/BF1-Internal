#include "stdafx.h"

//HOOKED FUNCTIONS

BOOL hkBitBlt(HDC destination, int x_destination, int y_destination, int width, int height, HDC source, int x_source, int y_source, DWORD rop)
{
	auto PO = SSCleaner->BitBltHook->GetProtectionObject();
	//Log->AddLog("[BB] %i %i\n", x_destination, y_destination);
	return false; //SSCleaner->oBitBlt(destination, x_destination, y_destination, width, height, source, x_source, y_source, rop);
}

void hkCopyResource(ID3D11DeviceContext* DeviceContext, ID3D11Resource* DestResource, ID3D11Resource* SrcResource)
{
	auto PO = SSCleaner->CopyResourceHook->GetProtectionObject();

	if (DestResource)
	{
		ID3D11Texture2D* texture_2d = static_cast<ID3D11Texture2D*>(DestResource);
		D3D11_TEXTURE2D_DESC desc;
		texture_2d->GetDesc(&desc);

		if (desc.Width >= static_cast<unsigned int>(DX11->ScreenSX - 25.0f) && desc.Height >= static_cast<unsigned int>(DX11->ScreenSY - 25.0f) && desc.CPUAccessFlags & D3D11_CPU_ACCESS_READ && desc.Usage == D3D11_USAGE_STAGING)
			return SSCleaner->oCopyResource(DeviceContext, DestResource, SSCleaner->GetCleanSS());
	}

	return SSCleaner->oCopyResource(DeviceContext, DestResource, SrcResource);
}

void hkCopySubresourceRegion(ID3D11DeviceContext* device_context, ID3D11Resource* destination_resource, unsigned int destination_subresource, unsigned int destination_x, unsigned int destination_y, unsigned int destination_z, ID3D11Resource* source_resource, unsigned int source_subresource, const D3D11_BOX* source_box)
{
	auto PO = SSCleaner->CopySubresourceHook->GetProtectionObject();

	if (destination_resource)
	{
		ID3D11Texture2D* texture_2d = static_cast<ID3D11Texture2D*>(destination_resource);
		D3D11_TEXTURE2D_DESC desc;
		texture_2d->GetDesc(&desc);

		if (desc.Width <= 1000 && desc.Height <= 500)
		{
			Game::CTime Timec = Game::GetHour();
			//Log->AddLog("PiBiEsEs (%i, %i) \n", desc.Width, desc.Height);
			return SSCleaner->oCopySubresource(device_context, destination_resource, destination_subresource, destination_x, destination_y, destination_z, SSCleaner->GetCleanSS(), source_subresource, source_box);
		}
	}

	return SSCleaner->oCopySubresource(device_context, destination_resource, destination_subresource, destination_x, destination_y, destination_z, source_resource, source_subresource, source_box);
}

//SETTING UP EVERYTHING

bool CSSCleaner::HookBitBlt()
{
	BitBltHook = new PLH::VEHHook();
	BitBltHook->SetupHook((BYTE*)(GetProcAddress(GetModuleHandle(L"gdi32.dll"), "BitBlt")), (BYTE*)hkBitBlt, PLH::VEHHook::VEHMethod::INT3_BP);
	BitBltState = BitBltHook->Hook();
	oBitBlt = BitBltHook->GetOriginal<BitBlt_t>();
	/*if (BitBltState)
		Log->AddLog("BB Hooked at %I64X\n", (QWORD)oBitBlt);*/
	return BitBltState;
}

bool CSSCleaner::HookCopyResource()
{
	QWORD* DeviceContextVT = *(QWORD**)(DX11->DX11DeviceContext);
	CopyResourceHook = new PLH::VEHHook();
	CopyResourceHook->SetupHook((BYTE*)DeviceContextVT[47], (BYTE*)hkCopyResource, PLH::VEHHook::VEHMethod::INT3_BP);
	CopyResourceState = CopyResourceHook->Hook();
	oCopyResource = CopyResourceHook->GetOriginal<CopyResource_t>();
	/*if (CopyResourceState)
		Log->AddLog("CR Hooked at %I64X\n", (QWORD)oCopyResource);*/
	return CopyResourceState;
}

bool CSSCleaner::HookCopySubresourceRegion()
{
	QWORD* DeviceContextVT = *(QWORD**)(DX11->DX11DeviceContext);
	CopySubresourceHook = new PLH::VEHHook();
	CopySubresourceHook->SetupHook((BYTE*)DeviceContextVT[46], (BYTE*)hkCopySubresourceRegion, PLH::VEHHook::VEHMethod::INT3_BP);
	CopySubresourceRegionState = CopySubresourceHook->Hook();
	oCopySubresource = CopySubresourceHook->GetOriginal<CopySubresourceRegion_t>();
	/*if (CopySubresourceRegionState)
		Log->AddLog("CSR Hooked at %I64X\n", (QWORD)oCopySubresource);*/
	return CopySubresourceRegionState;
}

void CSSCleaner::TakeSS()
{
	if (CurrentSSTick - LastSSTick > 30000)
	{
		NeedSS = true;
		LastSSTick = CurrentSSTick;
		return;
	}

	if (NeedSS)
	{
		ID3D11Texture2D* ScreenShotBuffer = nullptr;
		D3D11_TEXTURE2D_DESC ScreenShot;
		HRESULT hr = DX11->DX11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&ScreenShotBuffer));
		memset(&ScreenShot, 0, sizeof(D3D11_TEXTURE2D_DESC));

		ScreenShotBuffer->GetDesc(&ScreenShot);
		DX11->DX11Device->CreateTexture2D(&ScreenShot, NULL, &CleanSS);
		DX11->DX11DeviceContext->CopyResource(CleanSS, ScreenShotBuffer);

		ScreenShotBuffer->Release();
		ScreenShotBuffer = nullptr;
		NeedSS = false;
	}

	CurrentSSTick = GetTickCount();
}

std::unique_ptr<CSSCleaner> SSCleaner;