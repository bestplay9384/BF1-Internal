#pragma once

class ClientSoldierPrediction
{
public:
	char pad0[0x60];
	Vector3 position;
	char pad1[20];
	Vector3 velocity;

public: 
	Vector3 getPosition() {
		return position;
	}

	Vector3 getVelocity() {
		return velocity;
	}
};