#pragma once
#include "ISteeringBehaviorsCalculator.h"

class Flee : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
};
