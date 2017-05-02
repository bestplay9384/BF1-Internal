#pragma once

class ClientSpectatorList {
public:

	ClientSpectator* GetSpectator(const uint& _i)
	{
		ClientSpectator* _spectator = Mem::Read<ClientSpectator*>((QWORD)this + 0x28 + (_i * 0x8));
		if (Mem::IsValid(_spectator) && _spectator->IsSpectator())
			return _spectator;
		return nullptr;
	}

};