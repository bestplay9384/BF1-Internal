#pragma once

class GameContext {
public: // data offsets
	char pad0[0x0030]; // 0x0000
	Level* level; // 0x0030
	char pad1[0x0030]; // 0x0038 
	ClientPlayerManager* clientPlayerManager; //0x0068 
	
public: // methods
	static GameContext* getInstance() {
		return Mem::Read<GameContext*>(OFFSET_GAMECONTEXT);
	}

	ClientPlayerManager* getClientPlayerManager() {
		return Mem::Read<ClientPlayerManager*>((QWORD)&clientPlayerManager);
	}

	Level* getLevel() {
		return Mem::Read<Level*>((QWORD)&level);
	}
};