#pragma once
class ClientSoldierWeaponsComponent
{
public:
	char pad0[0x0900]; //0x0000
	ClientActiveWeaponHandler* activeWeaponHandler; //0x0900 
	char pad1[0x58]; // 0x0908
	unsigned int m_ActiveSlot; //0x0960 
	unsigned int m_LastActiveSlot; //0x0964 
	unsigned int m_LastGunIndex; //0x0968 
	char pad2[32];
	unsigned int m_CurrentZoomLevel; //0x098C 
	unsigned int m_MaxZoomLevel; //0x0990 
	char pad3[684];

public:
	ClientActiveWeaponHandler* getActiveWeaponHandler() {
		return Mem::Read<ClientActiveWeaponHandler*>((QWORD)&activeWeaponHandler);
	}

	unsigned int getActiveSlot() {
		return m_ActiveSlot;
	}
};//Size=0x0C40