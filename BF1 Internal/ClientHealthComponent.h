#pragma once

class ClientHealthComponent {
public:
	char pad0[0x20];
	float HP;
public:
	float getHP() {
		return HP;
	}
};