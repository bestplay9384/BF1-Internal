#pragma once

class PhysicsManager {
public:
	char pad0[0x88]; // 0x0000
	RayCaster* rayCaster; // 0x0088

public:
	RayCaster* getRayCaster() {
		return Mem::Read<RayCaster*>((QWORD)&rayCaster);
	}
};