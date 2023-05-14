﻿#pragma once
#include "ISteeringBehaviorsCalculator.h"

class Pursuit : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
	bool CheckUseSeek(const FVector2d& InToEvader, const FVector2D& InOwnerHeadingDirection, const FVector2D& InEvaderHeadingDirection);
	virtual float GetWeight() const override { return m_Weight; }
	
private:
	float m_Weight = 1.0f;
};
