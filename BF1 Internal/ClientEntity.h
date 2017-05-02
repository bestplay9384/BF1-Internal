#pragma once

class ClientEntity {
	public:
		char pad0[0x40];
		char Name[32];
		char pad1[7124];
		BYTE teamId; //0x1C34
		char pad2[259];
		ClientVehicleEntity* vehicle; // 0x1D38
		char pad3[8];
		ClientSoldierEntity* soldier; //0x1D48

		const char* getName() {
			std::string Name = Mem::ReadPtr<char*>({ (QWORD)this, 0x30, 0x130 }, false);
			if (Name.size() <= 4)
				return "";
			if (Name.find("vehicles.") != -1)
				Name = Name.substr(8, Name.length());
			return Name.c_str();
		}

		ClientSoldierEntity* getSoldier() {
			return Mem::Read<ClientSoldierEntity*>((QWORD)this + 0x1D48);
			//return Mem::Read<ClientSoldierEntity*>((QWORD)&soldier);
		}

		ClientVehicleEntity* getVehicle() {
			return Mem::Read<ClientVehicleEntity*>((QWORD)this + 0x1D38);
			//return Mem::Read<ClientVehicleEntity*>((QWORD)&vehicle);
		}

		BYTE getTeam() {
			return Mem::Read<BYTE>((QWORD)this + 0x1C34);
			//return teamId;
		}

		QWORD getPlayerView() {
			return Mem::Read<QWORD>((QWORD)this + 0x1D98); // TO FIX - wychodzi poza strukture CEntity
		}
};