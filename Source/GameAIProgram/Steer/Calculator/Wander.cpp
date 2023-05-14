#include "Wander.h"

#include "MatrixTypes.h"
#include "Define/Matrix.h"
#include "Kismet/KismetMathLibrary.h"
#include "Vehicle/Vehicle.h"
#include "Steer/SteeringBehaviors.h"
#include "Steer/SteeringParameter/SteeringParameterWander.h"

FVector2d Wander::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	TWeakObjectPtr<AVehicle> OwnerVehicle = InOwner.Pin()->GetSteeringTarget();
	auto SteeringParamWander = InOwner.Pin()->GetSteeringParamWander();
	if (IsValid(SteeringParamWander) == false)
		return {};
	
	FVector2d RandomTargetWanderDirection = GetRandomTargetWanderDirection(SteeringParamWander->WanderJitter);
	FVector2d TargetWander = InOwner.Pin()->GetTargetWander();
	TargetWander += RandomTargetWanderDirection;
	TargetWander.Normalize();
	TargetWander *= SteeringParamWander->WanderRadius;
	InOwner.Pin()->SetTargetWander(TargetWander);
	
	FVector2d TargetLocalPos = TargetWander + FVector2d(SteeringParamWander->WanderDistance, 0);
	FVector2d OwnerPos = OwnerVehicle->GetPos2d();
	FVector2d TargetToWorldPos = GameAI::Matrix::PointToWorldSpace(TargetLocalPos, OwnerVehicle->GetHeadingDirection(),
		OwnerVehicle->GetSideDirection(), OwnerPos);
	
	return TargetToWorldPos - OwnerPos;
}

FVector2d Wander::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}

FVector2d Wander::GetRandomTargetWanderDirection(const double& InWanderJitter)
{
	return FVector2d(RandomClamped() * InWanderJitter, RandomClamped() * InWanderJitter);
}

float Wander::RandomClamped()
{
	return FMath::RandRange(-1.0f, 1.0f);
}