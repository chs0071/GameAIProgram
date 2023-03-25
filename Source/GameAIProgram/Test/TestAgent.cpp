#pragma once
#include "Misc/AutomationTest.h"
#include "EngineUtils.h"
#include "TargetActor.h"
#include "Editor/EditorEngine.h"
#include "Steer/SteeringBehaviors.h"
#include "Steer/Calculator/ObstacleAvoidance.h"
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAIAgentSetTargetTest, "AI.Agent.SetTarget",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::RequiresUser| EAutomationTestFlags::EngineFilter)

bool FAIAgentSetTargetTest::RunTest(const FString& Parameters)
{
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTestCallReflectionFunction, "AI.FTestCallReflectionFunction",
								 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::RequiresUser| EAutomationTestFlags::EngineFilter)

bool FTestCallReflectionFunction::RunTest(const FString& Parameters)
{
	ObstacleAvoidance LocalOA;

	TArray<AVehicle*> LocalVehicles = GetVehicles();
	AVehicle* LocalVehicle = LocalVehicles[0];
	
	LocalOA.Execute(LocalVehicle->GetSteeringBehaviors());
	
	return true;
}
