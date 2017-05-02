#pragma once

class FiringFunctionData
{
public:
	char padx1[0x60];
	Vector3 SpawnOffset;
	char padx2[0x88 - sizeof(Vector3)];
	float bulletVelocity; //0x0088 
	char _0x008C[52];
	BulletEntityData* m_pBulletEntityData; //0x00C0 [BulletEntityData]
	char _0x00C8[24];
	__int32 m_numberOfBulletsPerShell; //0x00E0 
	float m_numberOfBulletsPerShot; //0x00E4 
	__int32 m_numberOfBulletsPerBurst; //0x00E8 
	char _0x00EC[4];
	BYTE m_relativeTargetAiming; //0x00F0 
	BYTE m_forceSpawnToCamera; //0x00F1 
	BYTE m_activeForceSpawnToCamera; //0x00F2 
	BYTE m_SpawnVisualAtBone; //0x00F3 
	char _0x00F4[256];
	float m_TriggerPullWeight; //0x01F4 
	float m_RateOfFire; //0x01F8 
	float m_RateOfFireForBurst; //0x01FC 
	float m_ClientFireRateMultiplier; //0x0200 
	float m_ReloadDelay; //0x0204 
	float m_ReloadTime; //0x0208 

public:
	BulletEntityData* getBulletEntityData() {
		return Mem::Read<BulletEntityData*>((QWORD)&m_pBulletEntityData);
	}

	Vector3 getSpawnOffset() {
		return SpawnOffset;
	}

	float getNumberOfBulletsPerShot() {
		return m_numberOfBulletsPerShot;
	}

	void setNumberOfBulletsPerShot(float val) {
		m_numberOfBulletsPerShot = val;
	}

	float getRateOfFireForBurst() {
		return m_RateOfFireForBurst;
	}

	void setRateOfFireForBurst(float val) {
		m_RateOfFireForBurst = val;
	}

	float getBulletVelocity() {
		return bulletVelocity;
	}

	void setBulletVelocity(float val) {
		bulletVelocity = val;
	}

};//Size=0x0440