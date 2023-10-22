#pragma once
#include "Define/Vector2d.h"
#include "Actor/AIActorBase.h"
#include "WallBase.generated.h"

UCLASS()
class AUWallBase : public AAIActorBase
{
	GENERATED_BODY()

public :
	FVector2d GetFrom() const;
	FVector2d GetTo() const;
	FVector2d GetNormal() const;
	FVector2d GetReverseNormal();
	bool IsActorInnerWall();
	
public:
	UPROPERTY()
	float WallLength = 100.0f;

	
};
