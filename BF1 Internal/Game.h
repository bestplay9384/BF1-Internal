#pragma once

#include "stdafx.h"
#include "DX11.h"

void MainThread();

class Features
{
public:
	static bool ESP;
	static bool Aimbot;
	static bool ShowMenu;
	static bool ESPShowFriends;
	static bool ShowBones;
	static bool ShowVehicles;
	static bool ShowFOV;
	static bool ShowHealth;
	static bool ShowName;
	static bool ShowDistance;
	static bool ShowESPBoxes;
	static float ESPDistance;
	static bool NoRecoil;
	static bool NoBreath;
	static bool NoSway;
	static bool InstantHit;
	static bool Radar;
	static bool Crosshair;
};

class Game
{
public:

	static BOOLEAN ThreadState[3];
	static bool cursorOn;

	static ClientEntity* GetLocalPlayer()
	{
		//return GameContext::getInstance()->getClientPlayerManager()->getLocalPlayer();
		return Mem::Read<ClientEntity*>(Mem::Read<QWORD>(Mem::Read<QWORD>(OFFSET_GAMECONTEXT) + 0x68) + 0x578);
	}

	static ClientPlayerManager* GetClientPlayerManager()
	{
		//return GameContext::getInstance()->getClientPlayerManager();
		return Mem::Read<ClientPlayerManager*>(Mem::Read<QWORD>(OFFSET_GAMECONTEXT) + 0x68);
	}

	static ClientSpectatorList* GetClientSpectatorsList() {
		return Mem::Read<ClientSpectatorList*>(Mem::Read<QWORD>(Mem::Read<QWORD>(OFFSET_GAMECONTEXT) + 0x68) + 0x318);
	}

	static void ToggleGameCursor()
	{
		cursorOn = !cursorOn;
		//Mem::Write<bool>(OFFSET_CURSOR, cursorOn);
	}

	static ClientEntityList* GetEntityList()
	{
		//return GameContext::getInstance()->getClientPlayerManager()->getClientEntityList();
		return Mem::ReadPtr<ClientEntityList*>({ OFFSET_GAMECONTEXT, 0x68, 0x560 }, true);
	}

	static bool W2S(const Vector3& WorldPosition, Vector3& _out)
	{
		float mX = DX11->ScreenSX * 0.5f;
		float mY = DX11->ScreenSY * 0.5f;

		// ok
		//D3DXMATRIXA16 VPM = GameRenderer::getInstance()->getRenderView()->getGameRender();
		D3DXMATRIXA16 VPM = Mem::Read<D3DXMATRIXA16>(Mem::Read<QWORD>(Mem::Read<QWORD>(OFFSET_GAMERENDERER) + 0x60) + 0x460);

		_out.z = VPM(0, 3) * WorldPosition.x + VPM(1, 3) * WorldPosition.y + VPM(2, 3) * WorldPosition.z + VPM(3, 3);
		if (_out.z < 0.1f)
			return false;

		float x = VPM(0, 0) * WorldPosition.x + VPM(1, 0) * WorldPosition.y + VPM(2, 0) * WorldPosition.z + VPM(3, 0);
		float y = VPM(0, 1) * WorldPosition.x + VPM(1, 1) * WorldPosition.y + VPM(2, 1) * WorldPosition.z + VPM(3, 1);

		_out.x = mX + mX * x / _out.z;
		_out.y = mY - mY * y / _out.z;

		if (_out.x <= 0.f || _out.x >= 1920 || _out.y <= 0.f || _out.y >= 1080)
			return false;

		return true;
	}

	struct CTime
	{
	public:
		int Hour;
		int Minute;
		CTime(int _hour, int _minute) : Hour(_hour), Minute(_minute) {}
	};

	static CTime GetHour()
	{
		time_t Tick = time(0);
		struct tm* Time = localtime(&Tick);
		return CTime(Time->tm_hour, Time->tm_min);
	}
};
