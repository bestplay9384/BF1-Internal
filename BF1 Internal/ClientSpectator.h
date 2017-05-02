#pragma once

class ClientSpectator
{
public:
	char pad0[0x40];
	char Name[32];

	bool IsSpectator()
	{
		return Mem::Read<bool>((QWORD)this + 0x1C31);
	}

	QWORD GetView()
	{
		return Mem::Read<QWORD>((QWORD)this + 0x1D98);
	}
};