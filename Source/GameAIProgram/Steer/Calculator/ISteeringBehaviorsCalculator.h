#pragma once
#include "Steer/SteeringBehaviors.h"

class ISteeringBehaviorsCalculator
{
public:
	virtual ~ISteeringBehaviorsCalculator() {}
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) = 0;
};
