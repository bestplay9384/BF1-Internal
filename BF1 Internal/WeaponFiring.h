#pragma once
class WeaponFiring {
public:
	char _0x0000[0x130]; // 0x0000
	WeaponFiringData* data; // 0x0130

	WeaponFiringData* getWeaponFiringData() {
		return Mem::Read<WeaponFiringData*>((QWORD)&data);
	}
};//Size=0x0440
