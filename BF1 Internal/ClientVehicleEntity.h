#pragma once

class ClientVehicleEntity
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

	BYTE getTeam()
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