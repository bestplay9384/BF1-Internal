#pragma once

class WeaponData {
public:
};

class WeaponModifier {
public:
};

class ClientWeapon {
public:
	char _0x0000[8];
	WeaponData* m_pWeaponData; //0x0008 [WeaponData]
	char _0x0010[8];
	WeaponFiringData* m_WeaponFiringData; //0x0018 [WeaponFiringData]
	WeaponModifier* m_pWeaponModifier; //0x0020 
	char _0x0028[8];
	D3DXVECTOR4 m_MoveSpeed; //0x0030 
	Matrix m_ShootSpace; //0x0040 
	Matrix m_ShootSpaceIdentity; //0x0080 
	char _0x00C0[560];
	Matrix m_matrix; //0x02F0 
	float m_CameraFOV; //0x0330 
	float m_WeaponFOV; //0x0334 
	float m_FOVScaleFactor; //0x0338 
	char _0x033C[16];
	__int32 m_ZoomLevel; //0x034C 
	char _0x0350[240];

public:
	Matrix getShootSpace() {
		return m_ShootSpace;
	}
};