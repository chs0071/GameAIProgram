#pragma once

#include "ISteeringBehaviorsCalculator.h"

class ABaseGameEntity;

class ObstacleAvoidance : public ISteeringBehaviorsCalculator
{
public:
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner) override;
	virtual FVector2d Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos) override;
	virtual float GetWeight() const override { return m_Weight; }
	
private:
	float GetDetectionBoxLength(TWeakObjectPtr<AVehicle>& InVehicle);
	void TagObstaclesWithinViewRange(TWeakObjectPtr<AVehicle>& InVehicle, const TArray<ABaseGameEntity*>& InObstacles, const float InDetectionBoxLength);

	ABaseGameEntity* GetClosetIntersectionObstacle(TWeakObjectPtr<AVehicle>& InVehicle,
	                                               const TArray<ABaseGameEntity*>& InObstacles);

	FVector2D GetSteeringForce(TWeakObjectPtr<AVehicle>& InVehicle, ABaseGameEntity* InClosetObstacle, const float InDetectionBoxLength);
	
	inline float GetMinDetectionBoxLength() const { return m_MinDetectionBoxLength; }  

private:
	const float m_MinDetectionBoxLength = 100.0f;
	float m_Weight = 10.0f;
};
