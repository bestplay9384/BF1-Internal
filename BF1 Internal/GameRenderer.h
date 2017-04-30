#pragma once

class GameRenderer {
public:
	char pad0[0x0060]; // 0x0000
	RenderView* renderView; // 0x0060

public:
	static GameRenderer* getInstance() {
		return Mem::Read<GameRenderer*>(OFFSET_GAMERENDERER);
	}

	RenderView* getRenderView() {
		return Mem::Read<RenderView*>((QWORD)&renderView);
	}
};