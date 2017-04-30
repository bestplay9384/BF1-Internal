#pragma once

class RenderView {
public:
	char pad0[0x460]; // 0x0000
	D3DXMATRIXA16 gameRender; // 0x0460

public:
	D3DXMATRIXA16 getGameRender() {
		return gameRender;
	}

};