#pragma once

class Level {
public:
	char pad0[0x108]; // 0x0000
	PhysicsManager* physicsManager; //0x0108

public:
	PhysicsManager* getPhysicsManager() {
		return Mem::Read<PhysicsManager*>((QWORD)&physicsManager);
	}
};
