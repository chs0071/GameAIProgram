// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameAIProgramGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEAIPROGRAM_API AGameAIProgramGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	static void SetTarget();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
};
