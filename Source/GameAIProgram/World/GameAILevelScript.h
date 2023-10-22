#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameAILevelScript.generated.h"

class ABaseGameEntity;

UCLASS()
class GAMEAIPROGRAM_API AGameAILevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	TArray<ABaseGameEntity*> GetObtacles() const;
	UFUNCTION(BlueprintImplementableEvent)
	TArray<AUWallBase*> GetWalls() const;
};
