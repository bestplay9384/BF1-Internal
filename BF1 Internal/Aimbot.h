#pragma once

#include "stdafx.h"

void AimbotThread();

class Aimbot
{
public:

	static float SmoothFactor;
	static float FOV;
	static float Distance;
	static int RetargetTimer;
	static int Bone;
	static bool RandomBone;
	static bool PrioritizeDistance;

	static Vector3 CalculateAngle(Vector3 _Target, Vector3 _LocalPos, Vector3 _Angles);

};