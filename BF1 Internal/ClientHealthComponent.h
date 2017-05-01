#pragma once

class ClientHealthComponent {
public:
	char pad0[0x20];
	float HP;
	float maxHealth;
	char pad1[0x1c];
	float vehicleHealth;

public:
	float getHP() {
		return HP;
	}
	float getMaxHP() {
		return maxHealth;
	}
	float getVehicleHP() {
		return vehicleHealth;
	}
};