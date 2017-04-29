#pragma once

#include "stdafx.h"
#include "DX11.h"

void MainThread();

class CSoldier;

class Features
{
public:
	static bool ESP;
	static bool Aimbot;
	static bool ShowMenu;
	static bool ESPShowFriends;
	static bool ShowBones;
	static bool ShowVehicles;
	static bool NoSway;
	static bool InstantHit;
	static bool ShowFOV;
	static bool ShowHealth;
	static bool ShowName;
	static bool ShowDistance;
	static bool ShowESPBoxes;
	static float ESPDistance;

};


enum eBones
{
	HEAD = 62, //
	HIP = 249, //
	STOMACH = 142, //
	CHEST = 146, //
	NECK = 50, //
	RIGHT_FEMUR = 299, // 
	RIGHT_KNEE = 295, //
	RIGHT_SHINBONE = 290, //
	RIGHT_MALLEOLUS = 290,
	RIGHT_TIPTOE = 291, // 
	RIGHT_SHOULDER = 164, //
 	RIGHT_BICEPS = 165, //
	RIGHT_ELBOW = 169, //
	RIGHT_ULNA = 170, //
	RIGHT_HAND = 170, //
	LEFT_FEMUR = 285, //
	LEFT_KNEE = 286, // 
	LEFT_SHINBONE = 276, //
	LEFT_MALLEOLUS = 276,
	LEFT_TIPTOE = 277,
	LEFT_SHOULDER = 160, //
	LEFT_BICEPS = 49, // 
	LEFT_ELBOW = 14, //
	LEFT_ULNA = 21, //
	LEFT_HAND = 21, //
};

class QuatTransform
{
public:
	Vector4 m_TransAndScale; 
	Vector4 m_Rotation;
}; 
class AxisAlignedBox
{
public:
	Vector4 m_Min; //0x0000 
	Vector4 m_Max; //0x0010 

	AxisAlignedBox()
	{}
};//Size=0x0020

class LinearTransform
{
public:
	union
	{
		struct
		{
			Vector3 left;
			Vector3 up;
			Vector3 forward;
			Vector3 trans;
		};
		FLOAT data[4][4];
	};
	LinearTransform()
	{}
};

struct TransformAABBStruct
{
	LinearTransform Transform;
	AxisAlignedBox AABB;
	Matrix pad;

	TransformAABBStruct()
	{}
};

class CHealthComponent
{
public:
	char pad0[0x20];
	float HP;
};

class ClientSoldierPrediction
{
public:
	char pad0[0x60];
	Vector3 Position;
	char pad1[20];
	Vector3 Velocity;
};

class ClientAimEntity {
public:
	/*char _0x0000[40];
	AimEntityData* m_pAimEntityData; //0x0028 [AimEntityData]
	char _0x0030[368];
	CSoldierEntity* m_pClientSoldierEntity; //0x01A0 [ClientSoldierEntity]
	ClientSoldierAimingSimulation* m_authorativeAiming; //0x01A8 
	char _0x01B0[1680];*/
};

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

extern std::map<QWORD, SwayDataSaved> SwayData;
extern std::map<QWORD, BulletDataSaved> BulletData;
//extern std::map<CSoldier*, bool> VisibleEntities;

class ClientWeapon {
public:
};

class SoldierAimingSimulationData {
public:
};

class SoldierWeaponBlueprint {
public:
};

class GunSwayData {
public:
	char pad0[0x03C8];
	float m_ShootingRecoilDecreaseScale; //0x03C8
	float m_FirstShotNoZoomDispersionMultiplier; //0x03CC
	float m_FirstShotZoomDispersionMultiplier; //0x03D0
	float m_FirstShotRecoilMultiplier; //0x03D4
	float m_PowerOfDispersionRandom; //0x03D8
};

class WeaponFiringData {
public:
	char _0x0000[0x38];
	GunSwayData* gunSwayData; //0x0038 [GunSwayData]
};//Size=0x0040

class WeaponFiring {
public:
	char _0x0000[0x18];
	WeaponFiringData* data;
};//Size=0x0440

class SoldierWeaponData {
public:
	char _0x0000[144];
	WeaponFiringData* weaponFiringData; //0x0090 [WeaponFiringData]
	char _0x0098[216];
	char* m_Name; //0x0170 
	char _0x0178[16];
	SoldierAimingSimulationData* m_pSoldierAimingSimulationData; //0x0188 [SoldierAimingSimulationData]
	char _0x0190[40];
	SoldierWeaponBlueprint* m_pSoldierWeaponBlueprint; //0x01B8 [SoldierWeaponBlueprint]
	char _0x01C0[640];
};

class ClientSoldierWeapon {
public:
	char _0x0000[48];
	SoldierWeaponData* soldierWeaponData; //0x0030 [SoldierWeaponData]
	char _0x0038[18840];
	__int64 m_ZoomLevelData1; //0x49D0 [ZoomLevelData]
	__int64 ZoomLevelData2; //0x49D8 [ZoomLevelData]
	char _0x49E0[48];
	ClientWeapon* m_pWeapon; //0x4A10 [ClientWeapon]
	char _0x4A18[16];
	WeaponFiring* weaponFiring; //0x4A18 
	char _0x4A30[1552];

};//Size=0x5040

class ClientSoldierWeaponsComponent {
public:
	char _0x0000[56];
	ClientSoldierWeapon* weapon; //0x0038 [ClientSoldierWeapon]
	char _0x0040[24];
	CSoldier* soldier; //0x0058 [ClientSoldierEntity]
	char _0x0060[96];
};

class CSoldier
{
public:
	char pad0[0x1C0]; //0x0000
	CHealthComponent* HealthComponent; //0x01C0
	char pad1[0x3E0]; // 0x01C8
	ClientSoldierPrediction* prediction; // 0x05A8
	char pad2[0xA8]; // 0x05B0
	ClientSoldierWeaponsComponent* weaponComponent; //0x0658 -- malo interesujacy
	char pad33[0x18]; // 0x660
	ClientAimEntity* aim;  //0x0678
	ClientSoldierWeapon* weapon; // 0x0680
	char pad_0680[0x20]; //0x0688
	BYTE m_isSprinting; //0x06A8
	char pad_06A9[2]; //0x06A9
	BYTE m_Occluded; //0x06AB
	char pad_06AC[0x980-0x6AB]; //0x06AC

	Vector3 GetPosition()
	{
		return prediction->Position;
	}

	Vector3 GetVelocity()
	{
		return prediction->Velocity;
	}

	float GetBulletVelocity()
	{
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, false);
	}

	void SetBulletVelocity(float _vel)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A30, 0x130, 0x10, 0x88 }, _vel, false);
	}

	void SetBulletGravity(float _gravity)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, _gravity, false);
	}

	float GetBulletGravity()
	{
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x140 }, false);
	}

	void SetInstantHit(BYTE _state)
	{
		Mem::WritePtr<BYTE>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x181 }, _state, false);
	}

	void SetTimeToLive(float _time)
	{
		Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, _time, false);
	}

	float GetTimeToLive()
	{
		return Mem::ReadPtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0xC0, 0x94 }, false);
	}

	QWORD GetWeapon()
	{
		//return weaponComponent->weapon->soldierWeaponData->weaponFiringData;
		return Mem::ReadPtr<QWORD>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30 }, false);
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
				if (SwayData[Weapon].Data[i])
					Mem::WritePtr<float>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x38, 0x10, offset }, SwayData[Weapon].Data[i], false);
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

	bool GetBonePosition(Vector3& outPos, DWORD ID)
	{
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

	Vector3 GetAngles()
	{
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, false);
	}

	BOOLEAN SetAngles(Vector3 _angles)
	{
		return Mem::WritePtr<Vector3>({ (QWORD)this, 0x678, 0x1A8, 0x28, 0x24 }, _angles, false);
	}

	Vector3 GetShootSpace()
	{
		return Mem::ReadPtr<Matrix>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A18, 0x40 }, false).Translation();
	}

	Vector3 GetSpawnOffset()
	{
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x658, 0x900, 0x38, 0x30, 0x90, 0x10, 0x60 }, false);
	}

	Vector3 GetInitialPosition()
	{
		return Mem::ReadPtr<Vector3>({ (QWORD)this, 0x658, 0x900, 0x38, 0x4A18, 0x40 }, false);
	}

	void SetChamsEnabled(BYTE btEnabled)
	{
		Mem::Write<BYTE>((QWORD)this + 0x5CD, btEnabled);
	}
};

class CVehicleEntity
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void Function23(); // 
	virtual void Function24();
	virtual void GetAABB(TransformAABBStruct* pAABB);
	virtual void GetTransform(Matrix* mTransform);

	BYTE GetTeam()
	{
		return Mem::Read<BYTE>((QWORD)this + 0x1C34);
	}

	std::string GetName()
	{
		std::string Name;
		Name = Mem::ReadPtr<char*>({ (QWORD)this, 0x30, 0x130 }, false);
		if (Mem::IsValid((QWORD*)((QWORD)this + 0x30)))
			Name = Name.substr(9, Name.size() - 9);
		return Name;
	}

};


class Element
{
public:
	Element* flink;
	Element* blink;
	int unknown0;
	int unknown1;
};

/*template <class T>
class EntityIterator
{
public:
	Element* first_element;
	Element* current_element;

	EntityIterator(GameWorld* game_world, intptr_t class_info)
	{
		using get_entity_list_fn = Element*(__thiscall*)(class_info, game_world);
		static get_entity_list_fn get_entity_list = reinterpret_cast<get_entity_list_fn>(0x1447941F0);

		first_element = get_entity_list(class_info, game_world);
		current_element = first_element;
	}

	bool has_next()
	{
		return current && current->flink;
	}

	Element* first()
	{
		return first_element;
	}

	Element* front()
	{
		return current_element;
	}

	Element* next()
	{
		return utility::valid_ptr(first_element) ? current_element = current_element->flink : nullptr;
	}
};*/

class MaterialDecl
{
public:
	uint32_t packed; //+0x0
};

class PhysicsId
{
protected:
	union
	{

		int32_t m_Id; //0x0000
		struct
		{
			uint16_t m_Index; //0x0000
			uint8_t m_Realm; //0x0002
			uint8_t m_Unk; //0x0003
		};
	};

public:

	int32_t Get()
	{
		return m_Id;
	}

	uint8_t GetRealm()
	{
		return m_Realm;
	}

	uint16_t GetIndex()
	{
		return m_Index;
	}

	operator int32_t()
	{
		return this->Get();
	}

	bool IsValid()
	{
		return this->Get() != -1;
	}

}; //0x0004

class RayCastHit
{
public:
	Vector4 position; //0x0000 
	Vector4 normal; //0x0010 
	PhysicsId physics_id; //0x0020
	MaterialDecl material; //0x0024
	uint32_t part; //0x0028
	uint32_t bone; //0x002C
	float lambda; //0x0030
	char _pad0[0xC];
}; //Size = 0x0070

template <class T>
class vector_
{
private:
	T* m_firstElement;
	T* m_lastElement;
	T* m_arrayBound;
	void* vftable;
public:
	size_t size()
	{
		return (((intptr_t)m_lastElement - (intptr_t)m_firstElement) / sizeof(void*));
	}

	T at(int nIndex)
	{
		return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
	}
	T operator [](int index)
	{
		return At(index);
	}
};



enum RayCastFlags
{
	NoCheck = 0,
	CheckDetailMesh = 0x0DB,
	IsAsyncRaycast = 0x2,
	DontCheckWater = 0x0FD,
	DontCheckTerrain = 0x07A,
	DontCheckRagdoll = 0x10,
	DontCheckCharacter = 0x20,
	DontCheckGroup = 0x40,
	DontCheckPhantoms = 0x80,
};

class RayCaster
{
public:
	virtual void Unknown();
	virtual bool PhysicsRayQuery(char* text, Vector4 *from, Vector4 *to, RayCastHit *hit, int flag, vector_<PhysicsId>* PhysicsEntityList);

	bool doshit(char* text, Vector4 *from, Vector4 *to, RayCastHit *hit, int flag, vector_<PhysicsId>* PhysicsEntityList)
	{
		typedef bool*(__thiscall *tFunc)(void*, char*, Vector4 *, Vector4 *, RayCastHit *, int, vector_<PhysicsId>*);
		tFunc testt = *(tFunc*)(*(QWORD*)this + 0x8);
		return testt(this, text, from, to, hit, flag, PhysicsEntityList);
	}

	static RayCaster* Get()
	{
		return Mem::ReadPtr<RayCaster*>({ OFFSET_GAMECONTEXT_2, 0x30, 0x108, 0x88 }, true);
	}

};

class BorderInputNode
{
public:
	char _pad0[0x8];
	void* input_cache; //0x0008
	char _pad1[0x40];
	void* input_node;  //0x0050

	static BorderInputNode* Get()
	{
		return (BorderInputNode*)(*((*(void***)BORDER_INPUT_NODE) + 1));
	}
};

class EntityInfo
{
public:
	char pad0[0x130];
	char Name[32];
};

class CSpectator
{
public:
	char pad0[0x40];
	char Name[32];

	bool IsSpectator()
	{
		return Mem::Read<bool>((QWORD)this + 0x1C31);
	}

	QWORD GetView()
	{
		return Mem::Read<QWORD>((QWORD)this + 0x1D98);
	}
};

class CEntity {
public:
	char pad0[0x40];
	char Name[32];
	char pad1[7124];
	BYTE teamId; //0x1C34
	char pad2[259];
	CVehicleEntity* vehicle; // 0x1D38
	char pad3[8];
	CSoldier* soldier; //0x1D48

	const char* GetName() {
		std::string Name = Mem::ReadPtr<char*>({ (QWORD)this, 0x30, 0x130 }, false);
		if (Name.size() <= 4)
			return "";
		if (Name.find("vehicles.") != -1)
			Name = Name.substr(8, Name.length());
		return Name.c_str();
	}

	CSoldier* GetSoldier() {
		return Mem::Read<CSoldier*>((QWORD)&soldier);
		//return Mem::Read<CSoldier*>((QWORD)soldier);
	}

	CVehicleEntity* GetCurrentVehicle() {
		return Mem::Read<CVehicleEntity*>((QWORD)&vehicle);
		//return Mem::Read<CVehicleEntity*>((QWORD)vehicle);
	}

	BYTE GetTeam() {
		return teamId;
	}

	QWORD GetPlayerView() {
		return Mem::Read<QWORD>((QWORD)this + 0x1D98); // TO FIX - wychodzi poza strukture CEntity
	}
};

class CEntityList {
public:
	CEntity* GetEntity(int i) {
		return Mem::Read<CEntity*>((QWORD)this + 0x38 + (i * 0x8));
	}
};

class CSpectatorList {
public:

	CSpectator* GetSpectator(const uint& _i)
	{
		CSpectator* _spectator = Mem::Read<CSpectator*>((QWORD)this + 0x28 + (_i * 0x8));
		if (Mem::IsValid(_spectator) && _spectator->IsSpectator())
			return _spectator;
		return nullptr;
	}

};

class ClientPlayerManager
{
public:

	virtual void function();
	virtual QWORD GetPlayers();
	virtual CSpectatorList* GetSpectators();

};

class Game
{
public:

	static BOOLEAN ThreadState[3];
	static bool cursorOn;

	static CEntity* GetLocalPlayer()
	{
		return Mem::Read<CEntity*>(Mem::Read<QWORD>(Mem::Read<QWORD>(OFFSET_GAMECONTEXT_2) + 0x68) + 0x578);
	}

	static ClientPlayerManager* GetClientPlayerManager()
	{
		return Mem::Read<ClientPlayerManager*>(Mem::Read<QWORD>(OFFSET_GAMECONTEXT_2) + 0x68);
	}

	static void ToggleGameCursor()
	{
		cursorOn = !cursorOn;
		//Mem::Write<bool>(OFFSET_CURSOR, cursorOn);
	}

	static CEntityList* GetEntityList()
	{
		return Mem::ReadPtr<CEntityList*>({ OFFSET_GAMECONTEXT_2, 0x68, 0x560 }, true);
	}

	static bool W2S(const Vector3& WorldPosition, Vector3& _out)
	{
		float mX = DX11->ScreenSX * 0.5f;
		float mY = DX11->ScreenSY * 0.5f;

		D3DXMATRIXA16 VPM = Mem::Read<D3DXMATRIXA16>(Mem::Read<QWORD>(Mem::Read<QWORD>(OFFSET_GAMERENDERER) + 0x60) + 0x460);

		_out.z = VPM(0, 3) * WorldPosition.x + VPM(1, 3) * WorldPosition.y + VPM(2, 3) * WorldPosition.z + VPM(3, 3);
		if (_out.z < 0.1f)
			return false;

		float x = VPM(0, 0) * WorldPosition.x + VPM(1, 0) * WorldPosition.y + VPM(2, 0) * WorldPosition.z + VPM(3, 0);
		float y = VPM(0, 1) * WorldPosition.x + VPM(1, 1) * WorldPosition.y + VPM(2, 1) * WorldPosition.z + VPM(3, 1);

		_out.x = mX + mX * x / _out.z;
		_out.y = mY - mY * y / _out.z;

		if (_out.x <= 0.f || _out.x >= 1920 || _out.y <= 0.f || _out.y >= 1080)
			return false;

		return true;
	}

	struct CTime
	{
	public:
		int Hour;
		int Minute;
		CTime(int _hour, int _minute) : Hour(_hour), Minute(_minute) {}
	};

	static CTime GetHour()
	{
		time_t Tick = time(0);
		struct tm* Time = localtime(&Tick);
		return CTime(Time->tm_hour, Time->tm_min);
	}
};
