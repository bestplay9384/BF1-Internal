#include "stdafx.h"

float GetAngleBetweenVectors3D(Vector3 v1, Vector3 v2);
Vector3 CalculatePerfectTrajectory(Vector3 From, Vector3 To, Vector3 EntityVelocity, float BulletVelocity, float Gravity);

float Aimbot::SmoothFactor = 0.035;
float Aimbot::FOV = 20.f;
float Aimbot::Distance = 100.f;
int Aimbot::Bone = HEAD;
int Aimbot::RetargetTimer = 200;
bool Aimbot::RandomBone = false;
bool Aimbot::PrioritizeDistance = true;

CSoldier* ActualTarget = nullptr;

bool IsAiming = false;

void AimbotThread()
{
	while (true)
	{
		CEntity* LocalPlayer = Game::GetLocalPlayer();
		if (Mem::IsValid(LocalPlayer) && Mem::IsValid(LocalPlayer->GetSoldier()))
		{
			CSoldier* LPSoldier = LocalPlayer->GetSoldier();
			if (Mem::IsValid(LPSoldier) && Mem::IsValid(LPSoldier->prediction) && Mem::IsValid(LPSoldier->aim))
			{
				ImGuiIO& io = ImGui::GetIO();
				unsigned int Slot = LPSoldier->GetActiveSlot();

				if (Slot == 0 || Slot == 1)
				{
					if (GetAsyncKeyState(0xA4) || GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LBUTTON))
					{
						if (!IsAiming)
						{
							IsAiming = true;
							if (Features::NoSway)
								LPSoldier->SetSpreadEnabled(true);
							if (Features::InstantHit)
								LPSoldier->SetBulletData(true);
						}
					}
					if (!GetAsyncKeyState(0xA4) && !GetAsyncKeyState(VK_RBUTTON) && !GetAsyncKeyState(VK_LBUTTON) && IsAiming)
					{
						IsAiming = false;
						ActualTarget = nullptr;
						if (Features::NoSway)
							LPSoldier->SetSpreadEnabled(false);
						if (Features::InstantHit)
							LPSoldier->SetBulletData(false);
					}
				}
			}
		}

		if ((GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(0xA4)) && Features::Aimbot)
		{
			CEntity* LocalPlayer = Game::GetLocalPlayer();
			if (Mem::IsValid(LocalPlayer) && Mem::IsValid(LocalPlayer->GetSoldier()))
			{
				CSoldier* LPSoldier = LocalPlayer->GetSoldier();
				if (Mem::IsValid(LPSoldier) && Mem::IsValid(LPSoldier->prediction) && Mem::IsValid(LPSoldier->aim))
				{
					unsigned int Slot = LPSoldier->GetActiveSlot();
					if (Slot == 0 || Slot == 1)
					{
						CEntityList* EntityList = Game::GetEntityList();
						Vector3 MyPos = LPSoldier->GetShootSpace() - LPSoldier->GetSpawnOffset();
						Vector3 MyAngles;
						if (MyPos.Length() <= 1.f)
							continue;

						float NearestOne = 750.f;
						Vector3 AimHere = Vector3::Zero;
						CSoldier* CurrentTarget = nullptr;
						int BoneToAim = -1;

						if (Mem::IsValid(EntityList))
						{
							for (int i = 0; i < 64; i++)
							{
								CEntity* Ent = EntityList->GetEntity(i);
								if (Mem::IsValid(Ent))
								{
									CSoldier* EntSoldier = Ent->GetSoldier();
									if (Mem::IsValid(EntSoldier) && Mem::IsValid(EntSoldier->HealthComponent) && Mem::IsValid(EntSoldier->prediction))
									{
										if (Ent->GetTeam() != LocalPlayer->GetTeam() && !EntSoldier->m_Occluded && Aimbot::Bone >= 0 && EntSoldier->HealthComponent->HP >= 1.f)
										{
											static const eBones RandBones[] = { HEAD, CHEST, HIP, STOMACH, NECK, RIGHT_FEMUR, LEFT_FEMUR, LEFT_KNEE, RIGHT_KNEE };
											if (!Aimbot::RandomBone)
												BoneToAim = Aimbot::Bone;
											else
												BoneToAim = static_cast<int>(RandBones[rand() % 9]);

											if (BoneToAim != -1)
											{
												Vector3 Pos;
												if (EntSoldier->GetBonePosition(Pos, BoneToAim))
												{
													MyAngles = LPSoldier->GetAngles();
													if (MyAngles.Length() != 0.f)
													{
														float dist = Vector3::Distance(MyPos, Pos);
														Vector3 SP;
														if (Game::W2S(Pos, SP))
														{
															if (Vector2::Distance(Vector2(SP.x, SP.y), Vector2(DX11->ScreenSX / 2.f, DX11->ScreenSY / 2.f)) <= Aimbot::FOV && dist >= 1.f && dist < Aimbot::Distance)
															{
																if (Aimbot::PrioritizeDistance)
																{
																	if (dist < NearestOne)
																	{
																		NearestOne = dist;
																		AimHere = Pos;
																		CurrentTarget = EntSoldier;
																	}
																}
																else
																{
																	NearestOne = dist;
																	AimHere = Pos;
																	CurrentTarget = EntSoldier;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						if (NearestOne <= Aimbot::Distance && CurrentTarget)
						{
							if (Mem::IsValid(&Mem::ReadPtr<Vector3>({ (QWORD)LPSoldier, 0x668, 0x1A8, 0x24, 0x24 }, false)))
							{
								if (ActualTarget && CurrentTarget != ActualTarget)
								{
									ActualTarget = nullptr;
									Sleep(Aimbot::RetargetTimer);
									continue;
								}
								MyAngles = LPSoldier->GetAngles();
								LPSoldier->SetAngles(Aimbot::CalculateAngle(AimHere, MyPos, MyAngles));
								ActualTarget = CurrentTarget;
							}
						}
					}
				}
			}
		}

		if (GetAsyncKeyState(VK_F8))
			break;

		Sleep(1);
	}

	Game::ThreadState[2] = FALSE;
}

void NormalizeAngle(Vector2& Angle)
{
	while (Angle.x <= -D3DX_PI)
		Angle.x += 2 * D3DX_PI;
	while (Angle.x > D3DX_PI)
		Angle.x -= 2 * D3DX_PI;
	while (Angle.y <= -D3DX_PI)
		Angle.y += 2 * D3DX_PI;
	while (Angle.y > D3DX_PI)
		Angle.y -= 2 * D3DX_PI;
}

void SmoothAngle(Vector2& From, Vector2& To, float Percent)
{
	Vector2 VecDelta = From - To;
	NormalizeAngle(VecDelta);
	VecDelta.x *= Percent;
	VecDelta.y *= Percent;
	To = From - VecDelta;
}

Vector3 CalculatePerfectTrajectory(Vector3 From, Vector3 To, Vector3 EntityVelocity, float BulletVelocity, float Gravity)
{
	return Vector3::Zero;
}

float GetAngleBetweenVectors3D(Vector3 v1, Vector3 v2)
{
	float numerator = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	float denominator = v1.Length() * v2.Length();
	float angle = acos(numerator / denominator) * (180.f / D3DX_PI);

	if (std::isnan(angle) || std::isinf(angle)) angle = 9999.f;

	return angle;
}

void Clamp(Vector3& VA)
{
	if (std::isnan(VA.x) || std::isnan(VA.y) || std::isnan(VA.z) || std::isinf(VA.x) || std::isinf(VA.y) || std::isinf(VA.z))
		return;
	if (VA.x > 360.f) VA.x -= 360.f;
	else if (VA.x < 0.f) VA.x += 360.f;
	if (VA.y > 89.f) VA.y -= 89.f;
	else if (VA.y < -85.f) VA.y += -85.f;
	VA.z = 0.f;
}

Vector3 Aimbot::CalculateAngle(Vector3 _Target, Vector3 _LocalPos, Vector3 _Angles)
{
	Vector3 vDirection = _Target - _LocalPos;
	Vector2 vFinal = Vector2(-atan2(vDirection.x, vDirection.z), atan2(vDirection.y, sqrtf(vDirection.x * vDirection.x + vDirection.z * vDirection.z)));

	SmoothAngle(Vector2(_Angles.x, _Angles.y), vFinal, Aimbot::SmoothFactor);

	return vFinal;
}
