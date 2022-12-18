// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameAIProgramGameModeBase.h"
#include "EngineUtils.h"
#include "TargetActor.h"
#include "Editor/EditorEngine.h"
#include "Steer/SteeringBehaviors.h"
#include "Vehicle/Vehicle.h"

inline ATargetActor* GetTargetActor()
{
	for (TActorIterator<ATargetActor> ActorItr(GWorld); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}
	return nullptr;
}


inline TArray<AVehicle*> GetVehicles()
{
	TArray<AVehicle*> Result;
	FWorldContext* LocalCurrentWorld = Cast<UEditorEngine>(GEngine)->GetPIEWorldContext();
	for (TActorIterator<AVehicle> ActorItr(LocalCurrentWorld->World()); ActorItr; ++ActorItr)
	{
		Result.Add(*ActorItr);
	}
	return Result;
}

void AGameAIProgramGameModeBase::SetTarget()
{
	ATargetActor* LocalTargetActor = GetTargetActor();
	TArray<AVehicle*> LocalVehicles = GetVehicles();
	for (AVehicle* Element : LocalVehicles)
	{
		TWeakPtr<FSteeringBehaviors> LocalSteeringBehaviors = Element->GetSteeringBehaviors();
		LocalSteeringBehaviors.Pin()->SetTargetPos(LocalTargetActor->GetActorLocation());
	}
}


void AGameAIProgramGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("Test.SetTarget"), TEXT(""),
		FConsoleCommandDelegate::CreateStatic(&AGameAIProgramGameModeBase::SetTarget), ECVF_Default);
}

