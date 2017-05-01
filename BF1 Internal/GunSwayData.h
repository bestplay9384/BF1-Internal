#pragma once

struct GunSwayDispersionData {
	float m_MinAngle; //0x0000
	float m_MaxAngle; //0x0004
	float m_IncreasePerShot; //0x0008
	float m_DecreasePerSecond; //0x000C
	float m_NoFireDecreasePerSecond; //0x0010
	float m_NoFireTimeThreshold; //0x0014
};

struct GunSwayDispersionModData {
	float m_MinAngleModifier; //0x0000
	float m_MaxAngleModifier; //0x0004
	float m_IncreasePerShotModifier; //0x0008
	float m_DecreasePerSecondModifier; //0x000C
	float m_NoFireDecreasePerSecondModifier; //0x0010
	float m_NoFireTimeThresholdModifier; //0x0014
	float m_FirstShotDispersionModifier; //0x0018
};

struct GunSwayRecoilData {
	float m_RecoilAmplitudeMax; //0x0000
	float m_RecoilAmplitudeIncPerShot; //0x0004
	float m_HorizontalRecoilAmplitudeIncPerShotMin; //0x0008
	float m_HorizontalRecoilAmplitudeIncPerShotMax; //0x000C
	float m_HorizontalRecoilAmplitudeMax; //0x0010
	float m_RecoilAmplitudeDecreaseFactor; //0x0014
};

struct GunSwayRecoilModData {
	float m_RecoilMagnitudeMod; //0x0000
	float m_RecoilAngleMod; //0x0004
	float m_FirstShotRecoilMod; //0x0008
	float m_RecoilAmplitudeDecreaseFactorMod; //0x000C
	float m_RecoilAngleOffset; //0x0010
};

struct GunSwayStanceTransition {
	GunSwayDispersionData m_MaxPenaltyValue; //0x0000
	float m_CoolDown; //0x0018
};

struct GunSwayBaseMoveJumpData {
	GunSwayDispersionData m_BaseValue; //0x0000
	GunSwayDispersionData m_Moving; //0x0018
	GunSwayDispersionData m_Jumping; //0x0030
	GunSwayDispersionData m_Sprinting; //0x0048
	GunSwayRecoilData m_Recoil; //0x0060
};

struct GunSwayStandData {
	GunSwayBaseMoveJumpData m_NoZoom; //0x0000
	GunSwayBaseMoveJumpData m_Zoom; //0x0078
};

struct GunSwayBaseMoveData {
	GunSwayDispersionData m_BaseValue; //0x0000
	GunSwayDispersionData m_Moving; //0x0018
	GunSwayRecoilData m_Recoil; //0x0030
};

struct GunSwayCrouchProneData {
	GunSwayBaseMoveData m_NoZoom; //0x0000
	GunSwayBaseMoveData m_Zoom; //0x0048
};

struct GunSwayStanceZoomModifierData {
	GunSwayDispersionModData m_DispersionMod; //0x0000
	GunSwayDispersionModData m_MovingDispersionMod; //0x001C
	GunSwayDispersionModData m_SprintingDispersionMod; //0x0038
	float m_RecoilMagnitudeMod; //0x0054
	float m_RecoilAngleMod; //0x0058
	float m_RecoilAngleOffset; //0x005C
	float m_FirstShotRecoilMod; //0x0060
	float m_RecoilAmplitudeDecreaseFactorMod; //0x0064
};


class GunSwayData {
public:
	
	GunSwayDispersionData* m_Dispersion; //0x0010
	GunSwayRecoilData* m_Recoil; //0x0018
	GunSwayStanceTransition* m_StanceTransitionDispersion; //0x0020
	GunSwayDispersionModData* m_SuppressionDispersionModifiers; //0x0028
	GunSwayRecoilModData* m_SuppressionRecoilModifiers; //0x0030
	GunSwayStandData m_Stand; //0x0038
	GunSwayCrouchProneData m_Crouch; //0x0128
	GunSwayCrouchProneData m_Prone; //0x01B8
	GunSwayStanceTransition m_ProneToCrouch; //0x0248
	GunSwayStanceTransition m_ProneToStand; //0x0264
	GunSwayStanceTransition m_CrouchToProne; //0x0280
	GunSwayStanceTransition m_CrouchToStand; //0x029C
	GunSwayStanceTransition m_StandToProne; //0x02B8
	GunSwayStanceTransition m_StandToCrouch; //0x02D4
	GunSwayStanceZoomModifierData m_SuppressionModifierUnzoomed; //0x02F0
	GunSwayStanceZoomModifierData m_SuppressionModifierZoomed; //0x0358
	//Array<GunSwayModifierUnlock> m_ModifierUnlocks; //0x03C0 -- dont need it
	char padx[8];

	float m_ShootingRecoilDecreaseScale; //0x03C8
	float m_FirstShotNoZoomDispersionMultiplier; //0x03CC
	float m_FirstShotZoomDispersionMultiplier; //0x03D0
	float m_FirstShotRecoilMultiplier; //0x03D4
	float m_PowerOfDispersionRandom; //0x03D8
	char _0x03DC[12];
	//CameraRecoilData* m_CameraRecoil; //0x03E0
	bool m_CameraRecoilWhenZoomed; //0x03E8
	char _0x03E9[7];

};