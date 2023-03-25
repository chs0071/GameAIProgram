#include "ObstacleAvoidance.h"

#include "Engine/LevelScriptBlueprint.h"
#include "Vehicle/Vehicle.h"
#include "World/GameAILevelScript.h"

FVector2d ObstacleAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	if(false == InOwner.IsValid())
		return FVector2d::Zero();

	auto LocalVehicle = InOwner.Pin()->GetSteeringTarget();
	if(false == LocalVehicle.IsValid())
		return FVector2d::Zero();

	auto LocalVehicleWorld = LocalVehicle.Get()->GetWorld();
	auto LocalLevelScriptActor = LocalVehicleWorld->GetLevelScriptActor();
	AGameAILevelScript* LocalLevelScript = Cast<AGameAILevelScript>(LocalLevelScriptActor);
	
	const TArray<ABaseGameEntity*>& LocalObstacles = LocalLevelScript->GetObtacles();

	if(LocalObstacles.IsEmpty())
	{
		int32 b = 0;
	}
	else
	{
		int32 c = 0;
	}
	
	int32 a = 0;
	
	return FVector2d::Zero();
}

FVector2d ObstacleAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return FVector2d::Zero(); 
}
