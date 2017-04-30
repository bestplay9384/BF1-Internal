#pragma once

class ClientEntityList {
public:
	ClientEntity* getEntity(int i) {
		return Mem::Read<ClientEntity*>((QWORD)this + 0x38 + (i * 0x8));
	}
};