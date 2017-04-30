#pragma once

class AimEntityData {
public:
};

class ClientSoldierEntity;

class ClientAimEntity {
public:
	char _0x0000[40];
	AimEntityData* m_pAimEntityData; //0x0028 [AimEntityData]
	char _0x0030[368];
	ClientSoldierEntity* m_pClientSoldierEntity; //0x01A0
	ClientSoldierAimingSimulation* m_authorativeAiming; //0x01A8
	char _0x01B0[1680];

public:
	ClientSoldierAimingSimulation* getAuthorativeAiming() {
		return Mem::Read<ClientSoldierAimingSimulation*>((QWORD)&m_authorativeAiming);
	}
};