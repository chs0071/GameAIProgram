#pragma once
#include "ISteeringBehaviorsCalculator.h"

class WallAvoidance : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
	virtual float GetWeight() const override { return m_Weight; }
	
	void CreateFeelers(TWeakPtr<FSteeringBehaviors> InOwner);
	FVector2d CalculateFeelerDirection(const FVector2d& InDirection, float InRadian);
	bool LineIntersection(const FVector2d& InFeelerPointA, const FVector2d& InFeelerPointB,
	                      const FVector2d& InWallPointA,
	                      const FVector2d& InWallPointB, double& OutDistance, FVector2d& OutAcrossPoint);
	bool IsAcrossLine(const FVector2d& InFeelerPointA, const FVector2d& InFeelerPointB, const FVector2d& InWallPointA,
	                  const FVector2d& InWallPointB);
	int CounterClockWise(const FVector2d& InLinePointA, const FVector2d& InLinePointB,
	                       const FVector2d& InTargetPoint);

private:
	TArray<GameAI::FVector2d> m_Feelers;
	float m_FeelerLength = 100.0f;
	float m_Weight = 1.0f;
};
