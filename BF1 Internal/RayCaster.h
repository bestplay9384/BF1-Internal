#pragma once

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

class MaterialDecl {
public:
	uint32_t packed; //+0x0
};

class PhysicsId {
protected:
	union {
		int32_t m_Id; //0x0000
		struct {
			uint16_t m_Index; //0x0000
			uint8_t m_Realm; //0x0002
			uint8_t m_Unk; //0x0003
		};
	};

public:
	int32_t Get() {
		return m_Id;
	}
	uint8_t GetRealm() {
		return m_Realm;
	}
	uint16_t GetIndex() {
		return m_Index;
	}
	operator int32_t() {
		return this->Get();
	}
	bool IsValid() {
		return this->Get() != -1;
	}

}; //0x0004

class RayCastHit {
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
class vector_ {
private:
	T* m_firstElement;
	T* m_lastElement;
	T* m_arrayBound;
	void* vftable;

public:
	size_t size() {
		return (((intptr_t)m_lastElement - (intptr_t)m_firstElement) / sizeof(void*));
	}
	T at(int nIndex) {
		return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
	}
	T operator [](int index) {
		return At(index);
	}
};

class RayCaster {
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
		return Mem::ReadPtr<RayCaster*>({ OFFSET_GAMECONTEXT, 0x30, 0x108, 0x88 }, true);
	}
};