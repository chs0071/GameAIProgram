#pragma once
#include "Steer/SteeringBehaviors.h"

class ISteeringBehaviorsCalculator
{
public:
	virtual ~ISteeringBehaviorsCalculator() {}
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) = 0;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) = 0;
	virtual float GetWeight() const = 0;
};
