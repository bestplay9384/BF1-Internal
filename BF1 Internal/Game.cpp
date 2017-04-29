#include "stdafx.h"

BOOLEAN Game::ThreadState[3] = { TRUE };
bool Game::cursorOn = false;

bool Features::ESP = true;
bool Features::Aimbot = true;
bool Features::ShowMenu = true;
bool Features::ESPShowFriends = false;
bool Features::ShowBones = true;
bool Features::ShowVehicles = true;
bool Features::NoSway = false;
bool Features::InstantHit = false;
bool Features::ShowFOV = true;
bool Features::ShowHealth = true;
bool Features::ShowName = true;
bool Features::ShowDistance = true;
bool Features::ShowESPBoxes = true;
float Features::ESPDistance = 999.f;

std::map<QWORD, SwayDataSaved> SwayData;
std::map<QWORD, BulletDataSaved> BulletData;
//std::map<CSoldier*, bool> VisibleEntities;

Vector3 posos;

void MainThread()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			Features::ShowMenu = !Features::ShowMenu;
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_F8))
			break;

		Sleep(10);
	}
	Game::ThreadState[1] = FALSE;
}