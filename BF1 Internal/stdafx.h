#pragma once
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "DirectXTK.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <Windows.h>
#include <CommonStates.h>
#include <DDSTextureLoader.h>
#include <Effects.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <PrimitiveBatch.h>
#include <ScreenGrab.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <SpriteFont.h>
#include <VertexTypes.h>
#include <DDSTextureLoader.h>
#include <D3DX11tex.h>
#include <DXGI.h>
#include <D3D11.h>
#include <D3DCompiler.h>
#include <DWrite.h>
#include <d3d9.h>
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <directxcolors.h>
#include <dwmapi.h>
#include <mutex>
#include <imagehlp.h>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <thread>
#include <map>
#include <glm/glm.hpp>
#include <Capstone/include/capstone.h>

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_PLACEMENT_NEW

typedef DWORD64 QWORD;


using namespace DirectX;
using namespace DirectX::SimpleMath;

#include "GFXUtils.h"
#include "imgui_internal.h"
#include "ImGuiDX11.h"
#include "Offsets.h"
#include "Resources/Purista.h"
#include "Resources/Shaders.h"
#include "IMem.h"
#include "IHook.h"
#include "PolyHook.h"
#include "SSCleaner.h"
#include "VMT.h"

// FrostBite dumped classes
#include "BorderInputNode.h"
#include "BonesList.h"
#include "GunSwayData.h"
#include "BulletEntityData.h"
#include "FiringFunctionData.h"
#include "WeaponFiringData.h"
#include "WeaponFiring.h"
#include "SoldierWeaponData.h"
#include "BreathControlHandler.h"
#include "ClientWeapon.h"
#include "ClientSoldierWeapon.h"
#include "ClientSoldierAimingSimulation.h"
#include "ClientAimEntity.h"
#include "ClientActiveWeaponHandler.h"
#include "ClientSoldierWeaponsComponent.h"
#include "ClientSoldierPrediction.h"
#include "ClientVehicleEntity.h"
#include "ClientSoldierEntity.h"
#include "ClientEntity.h"
#include "ClientEntityList.h"
#include "ClientHealthComponent.h"
#include "ClientSpectator.h"
#include "ClientSpectatorList.h"
#include "RenderView.h"
#include "RayCaster.h"
#include "PhysicsManager.h"
#include "Level.h"
#include "ClientPlayerManager.h"
#include "GameContext.h"
#include "GameRenderer.h"
#include "Aimbot.h"
#include "Game.h"
#include "DX11.h"