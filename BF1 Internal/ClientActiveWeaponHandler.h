#pragma once

class ClientSoldierEntity;

class ClientActiveWeaponHandler {
public:
	char _0x0000[56];
	ClientSoldierWeapon* weapon; //0x0038
	char _0x0040[24];
	ClientSoldierEntity* soldier; //0x0058
	char _0x0060[96];

public:
	ClientSoldierWeapon* getSoldierWeapon() {
		return Mem::Read<ClientSoldierWeapon*>((QWORD)&weapon);
	}

	ClientSoldierEntity* getSoldierEntity() {
		return Mem::Read<ClientSoldierEntity*>((QWORD)&soldier);
	}
};