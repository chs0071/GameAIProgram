#pragma once
#include "SteeringBehaviorsDefine.generated.h"

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBehaviorType
{
	None = 0,
	Seek = 1,
	Flee = 1 << 1,
	Arrive = 1 << 2,
	Wander = 1 << 3,
	Cohesion = 1 << 4,
	Separation = 1 << 5,
	Allignment = 1 << 6,
	Obstacle_Avoidance = 1 << 7,
	Wall_Avoidance = 1 << 8,
	FollowPath = 1 << 9,
	Pursuit = 1 << 10,
	Evade = 1 << 11,
	Interpose = 1 << 12,
	Hide = 1 << 13,
	Flock = 1 << 14,
	OffsetPursuit = 1 << 15,
};
ENUM_CLASS_FLAGS(EBehaviorType)

UENUM()
enum class ESummingMethod{Weighted_Average, Prioritized, Dithered};

UENUM()
enum class EDeceleration
{
	fast = 1,
	normal = 2,
	slow = 3,
};