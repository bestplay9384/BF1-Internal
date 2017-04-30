#pragma once

class ClientPlayerManager {
public:
	char pad0[0x560]; // 0x0000
	ClientEntityList* clientEntityList; // 0x0560
	char pad1[0x10]; // 0x0568
	ClientEntity* localPlayer; // 0x0578

public:
	ClientEntityList* getClientEntityList() {
		return Mem::Read<ClientEntityList*>((QWORD)&clientEntityList);
	}

	ClientEntity* getLocalPlayer() {
		return Mem::Read<ClientEntity*>((QWORD)&localPlayer);
	}
};