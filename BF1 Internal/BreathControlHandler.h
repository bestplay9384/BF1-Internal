#pragma once

class BreathControlHandler {
public:
	char pad0[0x0038]; // 0x0000
	float m_breathControlTimer; //0x0038
	float m_breathControlMultiplier; // 0x003C  
	float m_breathControlPenaltyTimer; // 0x0040  
	float m_breathControlpenaltyMultiplier; // 0x0044  
	float m_breathControlActive; // 0x0048  
	float m_breathControlInput; // 0x004C  
	float m_breathActive; // 0x0050
	char pad1[4]; // 0x0054
	float m_Enabled; // 0x0058  
};