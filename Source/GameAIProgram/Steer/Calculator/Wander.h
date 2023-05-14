#pragma once
#include "ISteeringBehaviorsCalculator.h"

class Wander : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
	FVector2d GetRandomTargetWanderDirection(const double& InWanderJitter);
	float RandomClamped();
	virtual float GetWeight() const override { return m_Weight; }
	
private:
	float m_Weight = 1.0f;
};
