#include "TestConsoleCommand.h"
#include "EngineUtils.h"
#include "TargetActor.h"
#include "Editor/EditorEngine.h"
#include "Steer/SteeringBehaviors.h"
#include "Vehicle/Vehicle.h"

namespace TestConsoleCommandCommon
{
	inline ATargetActor* GetTargetActor()
	{
		for (TActorIterator<ATargetActor> ActorItr(GWorld); ActorItr; ++ActorItr)
		{
			return *ActorItr;
		}
		return nullptr;
	}	
}

inline TArray<AVehicle*> GetVehicles()
{
	TArray<AVehicle*> Result;
	const FWorldContext* LocalCurrentWorld = Cast<UEditorEngine>(GEngine)->GetPIEWorldContext();
	for (TActorIterator<AVehicle> ActorItr(LocalCurrentWorld->World()); ActorItr; ++ActorItr)
	{
		Result.Add(*ActorItr);
	}
	return Result;
}

bool TestConsoleCommand::SetTarget()
{
	ATargetActor* LocalTargetActor = TestConsoleCommandCommon::GetTargetActor();
	TArray<AVehicle*> LocalVehicles = GetVehicles();
	for (AVehicle* Element : LocalVehicles)
		TWeakPtr<FSteeringBehaviors> LocalSteeringBehaviors = Element->GetSteeringBehaviors();

	return true;
}
