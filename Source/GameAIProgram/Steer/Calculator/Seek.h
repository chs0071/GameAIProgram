#pragma once
#include "ISteeringBehaviorsCalculator.h"

class Seek : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
};
