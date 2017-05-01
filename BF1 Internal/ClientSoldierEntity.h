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

	//float authorativeYaw; // 0x05C4 - no need
	//float authorativePitch; // 0x05FC - no need

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

	Vector3 getPosition() {
		return prediction->getPosition();
	}

	Vector3 getVelocity() {
		return prediction->getVelocity();
	}

	float GetBulletVelocity() {
		return weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getWeaponFiring()->getWeaponFiringData()->getFiringFunctionData()->getBulletVelocity();
		//return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, false);
	}

	void SetBulletVelocity(float _vel)
	{
		weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getWeaponFiring()->getWeaponFiringData()->getFiringFunctionData()->setBulletVelocity(_vel);
		//Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, _vel, false);
	}

	float GetBulletGravity()
	{
		return weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getBulletEntityData()->getGravity();
		//return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, false);
	}

	void SetBulletGravity(float _gravity)
	{
		weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getBulletEntityData()->setGravity(_gravity);
		//Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, _gravity, false);
	}

	void SetInstantHit(BYTE _state)
	{
		weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getBulletEntityData()->setInstantHit(_state);
		//Mem::WritePtr<BYTE>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x181 }, _state, false);
	}

	float GetTimeToLive()
	{
		return weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getBulletEntityData()->getTimeToLive();
		//return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, false);
	}

	void SetTimeToLive(float _time)
	{
		weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getBulletEntityData()->setTimeToLive(_time);
		//Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, _time, false);
	}

	QWORD GetWeapon()
	{
		return (QWORD)weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData();
		//return Mem::ReadPtr<QWORD>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30 }, false);
	}

	void SetBreath(bool _state) {
		QWORD Weapon = GetWeapon();

		if (!Mem::IsValid(&Weapon))
			return;


		if (!BreathData[Weapon].enabled)
		{
			BreathData[Weapon].num = breath->m_Enabled; //Mem::ReadPtr<float>({ (QWORD)this, 0x668, 0x58 }, false);
			BreathData[Weapon].enabled = true;
		}

		if (_state) // noBreath off
		{
			if (!BreathData[Weapon].enabled)
				return;

			breath->m_Enabled = BreathData[Weapon].num;
			//Mem::WritePtr<float>({ (QWORD)this, 0x668, 0x58 }, BreathData[Weapon].num, false);

		}
		else // noBreath on
		{
			breath->m_Enabled = 0.0f;
			//Mem::WritePtr<float>({ (QWORD)this, 0x668, 0x58 }, 0.0f, false);
		}
	}

	void SetRecoil(bool _state) {

		QWORD Weapon = GetWeapon();

		if (!Mem::IsValid(&Weapon))
			return;


		if (!RecoilData[Weapon].enabled)
		{
			RecoilData[Weapon].m_ShootingRecoilDecreaseScale = weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_ShootingRecoilDecreaseScale;
			RecoilData[Weapon].m_FirstShotNoZoomDispersionMultiplier = weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotNoZoomDispersionMultiplier;
			RecoilData[Weapon].m_FirstShotZoomDispersionMultiplier = weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotZoomDispersionMultiplier;
			RecoilData[Weapon].m_FirstShotRecoilMultiplier = weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotRecoilMultiplier;
			RecoilData[Weapon].m_PowerOfDispersionRandom = weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_PowerOfDispersionRandom;
			RecoilData[Weapon].enabled = true;
		}

		if (_state) // noRecoil off
		{
			if (!RecoilData[Weapon].enabled)
				return;

			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_ShootingRecoilDecreaseScale = RecoilData[Weapon].m_ShootingRecoilDecreaseScale;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotNoZoomDispersionMultiplier = RecoilData[Weapon].m_FirstShotNoZoomDispersionMultiplier;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotZoomDispersionMultiplier = RecoilData[Weapon].m_FirstShotZoomDispersionMultiplier;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotRecoilMultiplier = RecoilData[Weapon].m_FirstShotRecoilMultiplier;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_PowerOfDispersionRandom = RecoilData[Weapon].m_PowerOfDispersionRandom;
		}
		else // noRecoil on
		{
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_ShootingRecoilDecreaseScale = 100.0f;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotNoZoomDispersionMultiplier = 0.0f;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotZoomDispersionMultiplier = 0.0f;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_FirstShotRecoilMultiplier = 0.0f;
			weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_PowerOfDispersionRandom = 0.0f;
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
				SwayData[Weapon].Data.push_back(Mem::ReadPtr<float>({ (QWORD)weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_Dispersion, offset }, false));
			}
			SwayData[Weapon].enabled = true;
		}

		if (_state)
		{
			for (int i = 0; i < 0xFF; i++)
			{
				QWORD offset = (i * 0x4);
				Mem::WritePtr<float>({ (QWORD)weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_Dispersion, offset }, 0.0f, false);
			}
		}
		else
		{
			if (!SwayData[Weapon].enabled)
				return;

			for (int i = 0; i < 0xFF; i++)
			{
				QWORD offset = (i * 0x4);
				if (SwayData[Weapon].Data[i])
					Mem::WritePtr<float>({ (QWORD)weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getGunSwayData()->m_Dispersion, offset }, SwayData[Weapon].Data[i], false);
			}
		}

	}

	unsigned int GetActiveSlot()
	{
		return weaponComponent->getActiveSlot();
		//return Mem::ReadPtr<unsigned int>({ (QWORD)this, 0x658, 0x960 }, false);
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

	Vector3 GetAngles() { // dont know -- cant find offsets
		//aim->getAuthorativeAiming()->
		//return aim->getAuthorativeAiming()->m_pFpsAimer->m_yaw; --> float, used to be Vector3??
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, false);
	}

	BOOLEAN SetAngles(Vector3 _angles) { // dont know -- cant find offsets
		return Mem::WritePtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, _angles, false);
	}

	Vector3 GetShootSpace() {
		return (weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getClientWeapon()->getShootSpace()).Translation();
		//return Mem::ReadPtr<Matrix>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A18, 0x40 }, false).Translation();
	}

	Vector3 GetSpawnOffset() {
		return weaponComponent->getActiveWeaponHandler()->getSoldierWeapon()->getSoldierWeaponData()->getWeaponFiringData()->getFiringFunctionData()->getSpawnOffset();
		//return 0;
		//return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x60 }, false);
	}
};