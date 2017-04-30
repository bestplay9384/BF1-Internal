#pragma once
class WeaponFiringData {
public:
	char pad0[0x10];
	FiringFunctionData* m_FiringFunctionData; //0x0010 [FiringFunctionData]
	char pad1[0x20];
	GunSwayData* gunSwayData; //0x0038 [GunSwayData]

	GunSwayData* getGunSwayData() {
		return Mem::Read<GunSwayData*>((QWORD)&gunSwayData);
	}

	FiringFunctionData* getFiringFunctionData() {
		return Mem::Read<FiringFunctionData*>((QWORD)&m_FiringFunctionData);
	}
};//Size=0x0040