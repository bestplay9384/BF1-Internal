#pragma once
class ClientSoldierAimingSimulation
{
public:
	char _0x0000[16];
	SoldierAimingSimulationData* m_pSoldierAimingSimulationData; //0x0010 [SoldierAimingSimulationData]
	char _0x0018[24];
	char padxxx[8];
	//FpsAimer* m_pFpsAimer; //0x0030 Smart[SoldierAimAssistData]
	float m_yaw; //0x0038 
	float m_pitch; //0x003C 
	float m_aimYawTimer; //0x0040 
	float m_aimPitchTimer; //0x0044 
	D3DXVECTOR2 m_sway; //0x0048 
	char _0x0050[56];
	float m_zoomLevel; //0x0088 
	char _0x008C[4];
	D3DXMATRIX m_Transform; //0x0090 
	char _0x00D0[176];
	D3DXVECTOR3 m_RayPosition; //0x0180 
	char _0x018C[884];

};//Size=0x0500