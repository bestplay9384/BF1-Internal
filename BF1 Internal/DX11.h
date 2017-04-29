#ifndef DX11_INCLUDE
#define DX11_INCLUDE

#pragma once

#include "stdafx.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;

typedef __int16 GID;

class DXTKStateSaver;

struct CLog
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset
	bool                ScrollToBottom;

	void    Clear() { Buf.clear(); LineOffsets.clear(); }

	void    AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size);
		ScrollToBottom = true;
	}

	void    Draw(const char* title, bool* p_opened = NULL)
	{
		//ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
		//ImGui::Begin(title, p_opened);
		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling");
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
		if (copy) ImGui::LogToClipboard();

		if (Filter.IsActive())
		{
			const char* buf_begin = Buf.begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != NULL; line_no++)
			{
				const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
				if (Filter.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
		{
			ImGui::TextUnformatted(Buf.begin());
		}

		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::PopStyleVar();
		ImGui::EndChild();
		//ImGui::End();
	}
};


class GUI2
{
public:
	static Vector2 LastMousePosition;
	static Vector2 MousePosition;

	static void OnMouseMove(short x, short y);

};

class DX11Renderer : public GUI2
{
private:

	DWORD_PTR* SwapChainVtable = NULL;
	DWORD_PTR* DeviceContextVTable = NULL;

	ID3D11InputLayout*  InputLayout;

	D3D11_BLEND_DESC BlendStateDesc;
	ID3D11BlendState* AlphaOnBlendState;
	
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>> DX11Batch;
	std::unique_ptr<BasicEffect>						 DX11BatchEffects;
	std::unique_ptr<EffectFactory>						 DX11FXFactory;
	std::unique_ptr<CommonStates>						 DX11CommonStates;
	std::unique_ptr<SpriteBatch>						 DX11SpriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> LogoTexture;
	Microsoft::WRL::ComPtr<ID3D11Resource>			 LogoResource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			 Logo;
	CD3D11_TEXTURE2D_DESC						     LogoDesc;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> CursorTexture;
	Microsoft::WRL::ComPtr<ID3D11Resource>			 CursorResource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			 CursorGame;
	CD3D11_TEXTURE2D_DESC						     CursorDesc;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> UCIconTexture;
	Microsoft::WRL::ComPtr<ID3D11Resource>			 UCIconResource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			 UCIcon;
	CD3D11_TEXTURE2D_DESC						     UCIconDesc;

	HMODULE DllModule = NULL;

	const wchar_t* Target;

	BOOLEAN RestoreState = FALSE;
	BOOLEAN Initialized = FALSE;
	BOOLEAN Closing = FALSE;

	DXTKStateSaver* StateSaver;

	void DX11Begin();
	void DX11End();

	void CleanupDevice();

public:

	DX11Renderer() {}

	std::unique_ptr<SpriteFont>							 DX11Purista;

	ID3D11Device*			 DX11Device = nullptr;
	ID3D11DeviceContext*	 DX11DeviceContext = nullptr;
	ID3D11RenderTargetView*  DX11RenderTargetView = nullptr;
	ID3D11Texture2D*		 DX11BackBuffer = nullptr;
	IDXGISwapChain*			 DX11SwapChain = nullptr;

	static float ScreenX, ScreenY;
	static float ScreenSX, ScreenSY;

	float TestVar = 1.0f;

	HWND WTarget;

	DWORD InitDevice(HMODULE _DllModule, const wchar_t* HWNDTarget);
	BOOLEAN InitDX11RenderStuff(IDXGISwapChain* _SwapChain);

	void DX11RenderScene();

	std::wstring ConvertToWStr(const std::string& s);

	void DrawBox(float x, float y, float x1, float y1, Color color);
	void DrawEmptyBox(float x, float y, float x1, float y1, float px, Color color);
	void DrawEmptyBoxTab(float x, float y, float x1, float y1, float px, Color color);
	void DrawEmptyBoxTab_2(float x, float y, float x1, float y1, float from, float to, float px, Color color);
	void DrawDXText(float x, float y, float scale, bool center, float rot, Color color, bool shadow, const char* Format, ...);
	void DrawUnicodeText(float x, float y, float scale, bool center, float rot, Color color, bool shadow, std::wstring Format);

	void DrawLine(float x1, float y1, float x2, float y2, Color color);
	void DrawCircle(float x, float y, Color color, float radius, int _s);
	void DrawTriangle(float x, float y, Color color);
	void Draw3DBox(float x, float y, float x1, float y1, float movement, Color color);
	void DrawCursor(float x, float y, float size);

	void FillRGB(float x, float y, float x1, float y1, Color color);
};

class DXTKStateSaver
{
private:
	bool m_savedState;
	D3D_FEATURE_LEVEL m_featureLevel;
	ID3D11DeviceContext* m_pContext;
	D3D11_PRIMITIVE_TOPOLOGY m_primitiveTopology;
	ID3D11InputLayout* m_pInputLayout;
	ID3D11BlendState* m_pBlendState;
	float m_blendFactor[4];
	UINT m_sampleMask;
	ID3D11DepthStencilState* m_pDepthStencilState;
	UINT m_stencilRef;
	ID3D11RasterizerState* m_pRasterizerState;
	ID3D11ShaderResourceView* m_pPSSRV;
	ID3D11SamplerState* m_pSamplerState;
	ID3D11VertexShader* m_pVS;
	ID3D11ClassInstance* m_pVSClassInstances[256];
	UINT m_numVSClassInstances;
	ID3D11Buffer* m_pVSConstantBuffer;
	ID3D11GeometryShader* m_pGS;
	ID3D11ClassInstance* m_pGSClassInstances[256];
	UINT m_numGSClassInstances;
	ID3D11Buffer* m_pGSConstantBuffer;
	ID3D11ShaderResourceView* m_pGSSRV;
	ID3D11PixelShader* m_pPS;
	ID3D11ClassInstance* m_pPSClassInstances[256];
	UINT m_numPSClassInstances;
	ID3D11HullShader* m_pHS;
	ID3D11ClassInstance* m_pHSClassInstances[256];
	UINT m_numHSClassInstances;
	ID3D11DomainShader* m_pDS;
	ID3D11ClassInstance* m_pDSClassInstances[256];
	UINT m_numDSClassInstances;
	ID3D11Buffer* m_pVB;
	UINT m_vertexStride;
	UINT m_vertexOffset;
	ID3D11Buffer* m_pIndexBuffer;
	DXGI_FORMAT m_indexFormat;
	UINT m_indexOffset;

	DXTKStateSaver(const DXTKStateSaver&);
	//DXTKStateSaver& operator=(const DXTKStateSaver&);

public:
	DXTKStateSaver();
	~DXTKStateSaver();

	HRESULT saveCurrentState(ID3D11DeviceContext* pContext);
	HRESULT restoreSavedState();
	void ZeroShaders(ID3D11DeviceContext* pContext);
	void releaseSavedState();
};

template<class T> inline void SAFE_DELETE(T *&p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}

template<class T> inline void SAFE_DELETE_ARRAY(T *&p)
{
	if (p)
	{
		delete[] p;
		p = NULL;
	}
}

template<class T> inline void SAFE_RELEASE(T *&p)
{
	if (p)
	{
		p->Release();
		p = NULL;
	}
}

extern std::unique_ptr<DX11Renderer> DX11;
extern std::unique_ptr<CLog> Log;

#endif DX11_INCLUDE