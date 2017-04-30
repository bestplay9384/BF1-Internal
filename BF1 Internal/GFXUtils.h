#pragma once

class QuatTransform {
public:
	Vector4 m_TransAndScale;
	Vector4 m_Rotation;
};

class AxisAlignedBox {
public:
	Vector4 m_Min; //0x0000 
	Vector4 m_Max; //0x0010 

	AxisAlignedBox() {}
};//Size=0x0020

class LinearTransform {
public:
	union {
		struct {
			Vector3 left;
			Vector3 up;
			Vector3 forward;
			Vector3 trans;
		};
		FLOAT data[4][4];
	};
	LinearTransform() {}
};

struct TransformAABBStruct {
	LinearTransform Transform;
	AxisAlignedBox AABB;
	Matrix pad;
	TransformAABBStruct() {}
};