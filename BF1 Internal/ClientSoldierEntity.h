#pragma once

struct SwayDataSaved
{
	bool enabled = false;
	std::vector<float> Data;
};

struct BulletDataSaved
{
	bool enabled = false;
	float velocity;
	float time;
	float gravity;
	bool instantHit;
};

struct RecoilSaved {
	bool enabled = false;
	float m_ShootingRecoilDecreaseScale; //0x03C8
	float m_FirstShotNoZoomDispersionMultiplier; //0x03CC
	float m_FirstShotZoomDispersionMultiplier; //0x03D0
	float m_FirstShotRecoilMultiplier; //0x03D4
	float m_PowerOfDispersionRandom; //0x03D8
};

struct BreathSaved {
	bool enabled = false;
	float num;
};

extern std::map<QWORD, SwayDataSaved> SwayData;
extern std::map<QWORD, BulletDataSaved> BulletData;
extern std::map<QWORD, RecoilSaved> RecoilData;
extern std::map<QWORD, BreathSaved> BreathData;

class ClientHealthComponent;

class ClientSoldierEntity
{
public:
	char pad0[0x1C0]; //0x0000
	ClientHealthComponent* HealthComponent; //0x01C0
	char pad1[0x3E0]; // 0x01C8
	ClientSoldierPrediction* prediction; // 0x05A8
	char pad2[0xA8]; // 0x05B0
	ClientSoldierWeaponsComponent* weaponComponent; //0x0658 -- malo interesujacy
	char pad3[8]; // 0x660
	BreathControlHandler* breath; //0x0668
	char pad4[8]; // 0x0670
	ClientAimEntity* aim;  //0x0678
	ClientSoldierWeapon* weapon; // 0x0680
	char pad_0680[0x20]; //0x0688
	BYTE m_isSprinting; //0x06A8
	char pad_06A9[2]; //0x06A9
	BYTE m_Occluded; //0x06AB
	char pad_06AC[0x980 - 0x6AB]; //0x06AC

	void resetHealth() {
		Mem::WritePtr<float>({ (QWORD)this, 0x01C0, 0x20 }, 100.f, false);
	}

	Vector3 getPosition() {
		return Mem::Read<Vector3>(Mem::Read<QWORD>((QWORD)this + 0x5A8) + 0x60);
	}

	BYTE IsSprinting() {
		return Mem::Read<BYTE>((QWORD)this + 0x06A8);
	}

	BYTE IsOccluded()
	{
			return Mem::Read<BYTE>((QWORD)this + 0x6AB);
	}

	Vector3 getVelocity() {
		return Mem::Read<Vector3>(Mem::Read<QWORD>((QWORD)this + 0x5A8) + 0x80);
	}

	float GetBulletVelocity() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, false);
	}

	void SetBulletVelocity(float _vel)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, _vel, false);
	}

	float GetBulletGravity()
	{
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, false);
	}

	void SetBulletGravity(float _gravity)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, _gravity, false);
	}

	void SetInstantHit(BYTE _state)
	{
		Mem::WritePtr<BYTE>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x181 }, _state, false);
	}

	BYTE GetInstantHit() {
		return Mem::ReadPtr<BYTE>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x181 }, false);
	}

	float GetTimeToLive()
	{
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, false);
	}

	void SetTimeToLive(float _time)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, _time, false);
	}

	QWORD GetWeapon()
	{
		return Mem::ReadPtr<QWORD>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30 }, false);
	}

	float getBreath() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x668, 0x58 }, false);
	}

	void SetBreathEnabled(bool _state) {
		QWORD Weapon = GetWeapon();

		if (!Mem::IsValid(&Weapon))
			return;


		if (!BreathData[Weapon].enabled)
		{
			BreathData[Weapon].num = Mem::ReadPtr<float>({ (QWORD)this, 0x668, 0x58 }, false);
			BreathData[Weapon].enabled = true;
		}

		if (_state) // noBreath off
		{
			if (!BreathData[Weapon].enabled)
				return;

			Mem::WritePtr<float>({ (QWORD)this, 0x668, 0x58 }, BreathData[Weapon].num, false);

		}
		else // noBreath on
		{
			Mem::WritePtr<float>({ (QWORD)this, 0x668, 0x58 }, 0.0f, false);
		}
	}

	float getShootingRecoilDecreaseScale() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03C8 }, false);
	}

	float getFirstShotNoZoomDispersionMultiplier() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03CC }, false);
	}

	float getFirstShotZoomDispersionMultiplier() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D0 }, false);
	}

	float getFirstShotRecoilMultiplier() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D4 }, false);
	}

	float getPowerOfDispersionRandoms() {
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D8 }, false);
	}

	void setShootingRecoilDecreaseScale(float val) {
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03C8 }, val, false);
	}

	void setFirstShotNoZoomDispersionMultiplier(float val) {
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03CC }, val, false);
	}

	void setFirstShotZoomDispersionMultiplier(float val) {
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D0 }, val, false);
	}

	void setFirstShotRecoilMultiplier(float val) {
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D4 }, val, false);
	}

	void setPowerOfDispersionRandoms(float val) {
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x38, 0x03D8 }, val, false);
	}

	void SetRecoilEnabled(bool _state) {

		QWORD Weapon = GetWeapon();

		if (!Mem::IsValid(&Weapon))
			return;

		if (!RecoilData[Weapon].enabled)
		{

			RecoilData[Weapon].m_ShootingRecoilDecreaseScale = getShootingRecoilDecreaseScale();
			RecoilData[Weapon].m_FirstShotNoZoomDispersionMultiplier = getFirstShotNoZoomDispersionMultiplier();
			RecoilData[Weapon].m_FirstShotZoomDispersionMultiplier = getFirstShotZoomDispersionMultiplier();
			RecoilData[Weapon].m_FirstShotRecoilMultiplier = getFirstShotRecoilMultiplier();
			RecoilData[Weapon].m_PowerOfDispersionRandom = getPowerOfDispersionRandoms();
			RecoilData[Weapon].enabled = true;
		}

		if (_state) // noRecoil off
		{
			if (!RecoilData[Weapon].enabled)
				return;

			setShootingRecoilDecreaseScale(RecoilData[Weapon].m_ShootingRecoilDecreaseScale);
			setFirstShotNoZoomDispersionMultiplier(RecoilData[Weapon].m_ShootingRecoilDecreaseScale);
			setFirstShotZoomDispersionMultiplier(RecoilData[Weapon].m_FirstShotNoZoomDispersionMultiplier);
			setFirstShotRecoilMultiplier(RecoilData[Weapon].m_FirstShotRecoilMultiplier);
			setPowerOfDispersionRandoms(RecoilData[Weapon].m_PowerOfDispersionRandom);
		}
		else // noRecoil on
		{
			setShootingRecoilDecreaseScale(100.0f);
			setFirstShotNoZoomDispersionMultiplier(0.0f);
			setFirstShotZoomDispersionMultiplier(0.0f);
			setFirstShotRecoilMultiplier(0.0f);
			setPowerOfDispersionRandoms(0.0f);
		}

	}

	void SetSpreadEnabled(bool _state)
	{

		QWORD Weapon = GetWeapon();

		if (!Mem::IsValid(&Weapon))
			return;

		if (!SwayData[Weapon].enabled)
		{
			for (int i = 0; i < 0xFF; i++)
			{
				QWORD offset = (i * 0x4);
				SwayData[Weapon].Data.push_back(Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x38, 0x10, offset }, false));
			}
			SwayData[Weapon].enabled = true;
		}

		if (_state)
		{
			for (int i = 0; i < 0xFF; i++)
			{
				QWORD offset = (i * 0x4);
				Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x38, 0x10, offset }, 0.f, false);
			}
		}
		else
		{
			if (!SwayData[Weapon].enabled)
				return;

			for (int i = 0; i < 0xFF; i++)
			{
				QWORD offset = (i * 0x4);
				if (SwayData[Weapon].Data[i]) {
					Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x38, 0x10, offset }, SwayData[Weapon].Data[i], false);
				}	
			}
		}

	}

	unsigned int GetActiveSlot()
	{
		return Mem::ReadPtr<unsigned int>({ (QWORD)this, 0x658, 0x960 }, false);
	}

	void SetBulletData(bool _state)
	{
		QWORD Weapon = GetWeapon();
		if (!Mem::IsValid(&Weapon))
			return;

		if (!BulletData[Weapon].enabled)
		{
			BulletData[Weapon].instantHit = false;
			BulletData[Weapon].gravity = GetBulletGravity();
			BulletData[Weapon].time = GetTimeToLive();
			BulletData[Weapon].velocity = GetBulletVelocity();
			BulletData[Weapon].enabled = true;
		}

		if (_state)
		{
			SetBulletGravity(0.f);
			SetTimeToLive(1.f);
			SetBulletVelocity(9999.f);
			SetInstantHit(1);
		}
		else
		{
			if (!BulletData[Weapon].enabled)
				return;

			SetBulletGravity(BulletData[Weapon].gravity);
			SetTimeToLive(BulletData[Weapon].time);
			SetBulletVelocity(BulletData[Weapon].velocity);
			SetInstantHit(0);
		}
	}

	bool GetBonePosition(Vector3& outPos, DWORD ID) {
		Mem::Write<BYTE>((QWORD)this + 0x1B4, 1);
		Mem::Write<BYTE>((QWORD)this + 0x1A, 161);

		QuatTransform Temp = Mem::Read<QuatTransform>(Mem::Read<QWORD>(Mem::Read<QWORD>((QWORD)this + 0x460) + 0x20) + (ID * 0x20));

		if (Vector3(Temp.m_TransAndScale.x, Temp.m_TransAndScale.y, Temp.m_TransAndScale.z).Length() >= 1.f)
		{
			outPos.x = Temp.m_TransAndScale.x;
			outPos.y = Temp.m_TransAndScale.y;
			outPos.z = Temp.m_TransAndScale.z;
			return true;
		}
		return false;
	}

	Vector3 GetAngles() {
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, false);
	}

	BOOLEAN SetAngles(Vector3 _angles) {
		return Mem::WritePtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, _angles, false);
	}

	Vector3 GetShootSpace() {
		return Mem::ReadPtr<Matrix>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A18, 0x40 }, false).Translation();
	}

	Vector3 GetSpawnOffset() {
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x60 }, false);
	}
};