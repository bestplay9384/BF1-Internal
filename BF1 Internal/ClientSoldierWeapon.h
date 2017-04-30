#pragma once
class ClientSoldierWeapon {
public:
	char pad0[0x30]; // 0x0000
	SoldierWeaponData* soldierWeaponData; //0x0030
	char pad1[0x49e0]; // 0x0038
	ClientWeapon* m_pWeapon; //0x4A18 [ClientWeapon]
	char pad2[0x10]; // 0x4a20
	WeaponFiring* weaponFiring; //0x4A30 

public:
	SoldierWeaponData* getSoldierWeaponData() {
		return Mem::Read<SoldierWeaponData*>((QWORD)&soldierWeaponData);
	}

	ClientWeapon* getClientWeapon() {
		return Mem::Read<ClientWeapon*>((QWORD)&m_pWeapon);
	}

	WeaponFiring* getWeaponFiring() {
		return Mem::Read<WeaponFiring*>((QWORD)&weaponFiring);
	}

};//Size=0x5040