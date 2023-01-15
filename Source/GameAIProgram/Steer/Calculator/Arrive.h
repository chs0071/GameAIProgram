﻿#pragma once
#include "ISteeringBehaviorsCalculator.h"


class Arrive : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	void PrintArriveDebugMessage(const double& InSpeed, const FVector2d& InDesiredVelocity);
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
};
