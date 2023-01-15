#include "GameAIProgramGameModeBase.h"
#include "EngineUtils.h"
#include "Editor/EditorEngine.h"
#include "Steer/SteeringBehaviors.h"
#include "Vehicle/Vehicle.h"

UWorld* GetWorld()
{
	const FWorldContext* LocalCurrentWorld = Cast<UEditorEngine>(GEngine)->GetPIEWorldContext();
	if(nullptr == LocalCurrentWorld)
		return nullptr;
	
	return LocalCurrentWorld->World();
}

inline TArray<AVehicle*> GetVehicles()
{
	TArray<AVehicle*> Result;

	const UWorld* LocalWorld = GetWorld();
	if(false == IsValid(LocalWorld))
		return Result;
	
	for (TActorIterator<AVehicle> ActorItr(LocalWorld); ActorItr; ++ActorItr)
	{
		Result.Add(*ActorItr);
	}
	return Result;
}

void AGameAIProgramGameModeBase::SetTarget()
{
	TMap<FName, AVehicle*> LocalFindVehicle;
	TArray<AVehicle*> LocalVehicles = GetVehicles();

	for (AVehicle* Element : LocalVehicles)
	{
		if(Element->Tags.IsEmpty())
			continue;
		
		LocalFindVehicle.Add(Element->Tags[0], Element);
	}
	
	for (AVehicle* Element : LocalVehicles)
	{
		if(false == IsValid(Element))
			continue;

		if(Element->FollowTarget.IsNone())
			continue;

		AVehicle** LocalFindTarget = LocalFindVehicle.Find(Element->FollowTarget);
		if(nullptr == LocalFindTarget)
			continue;

		const AVehicle* LocalTargetVehicle = (*LocalFindTarget);
		if(false == IsValid(LocalTargetVehicle))
			continue;
		
		TWeakPtr<FSteeringBehaviors> LocalSteeringBehaviors = Element->GetSteeringBehaviors();
		LocalSteeringBehaviors.Pin()->SetTarget(LocalTargetVehicle);
	}
}

void AGameAIProgramGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	IConsoleManager::Get().RegisterConsoleCommand(TEXT("Test.SetTarget"), TEXT(""),
		FConsoleCommandDelegate::CreateStatic(&AGameAIProgramGameModeBase::SetTarget), ECVF_Default);
}

void AGameAIProgramGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetTarget();
}

