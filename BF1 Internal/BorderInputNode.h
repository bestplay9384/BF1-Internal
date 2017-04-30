#pragma once

class BorderInputNode
{
public:
	char _pad0[0x8];
	void* input_cache; //0x0008
	char _pad1[0x40];
	void* input_node;  //0x0050

public:
	static BorderInputNode* getInstance() {
		return (BorderInputNode*)(*((*(void***)BORDER_INPUT_NODE) + 1));
	}
};