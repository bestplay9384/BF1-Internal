#pragma once

class BulletEntityData
{
public:
	char pad0[0x94]; // 0x0000
	float m_timeToLive; // 0x0094
	char pad1[0xa8]; // 0x0098
	float m_gravity; //0x0140 
	float m_impactImpulse; //0x0144 
	float m_detonationTimeVariation; //0x0148 
	float m_vehicleDetonationRadius; //0x014C 
	float m_vehicleDrtonationActivationDelay; //0x0150 
	float m_flyBySoundRadius; //0x0154 
	float m_flyBySoundSpeed; //0x0158 
	float m_firstFraneTravelDistance; //0x015C 
	float m_distributeDamageOverTime; //0x0160 
	char _0x0164[4];
	float m_StartDamage; //0x0168 
	float m_EndDamage; //0x016C 
	float m_DamageFallOff; //0x0170 
	float m_DamageFallOffEndDistance; //0x0174 
	float m_TimeToArmExplosion; //0x0178 
	char _0x017C[4];
	BYTE m_bHasVehicleDetination; //0x0180 
	BYTE m_bInstantHit; //0x0181 
	BYTE m_bStopTrail; //0x0182 
	char _0x0183[701];
public:
	float getGravity() {
		return m_gravity;
	}
	BYTE getInstantHit() {
		return m_bInstantHit;
	}
	float getTimeToLive() {
		return m_timeToLive;
	}

	void setGravity(float val) {
		m_gravity = val;
	}
	void setInstantHit(BYTE val) {
		m_bInstantHit = val;
	}
	void setTimeToLive(float val) {
		m_timeToLive = val;
	}

};//Size=0x0440