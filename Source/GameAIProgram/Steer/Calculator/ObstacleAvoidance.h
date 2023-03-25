#pragma once
#include "ISteeringBehaviorsCalculator.h"

class ObstacleAvoidance : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
};
