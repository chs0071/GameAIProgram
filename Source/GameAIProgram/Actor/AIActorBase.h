#pragma once
#include "Define/Vector2d.h"
#include "AIActorBase.generated.h"

UCLASS()
class AAIActorBase : public AActor
{
	GENERATED_BODY()
public:
	FVector GetPos() const;
	FVector2d GetPos2d() const;
	void SetPos(const FVector& InPos);
	float GetScale() const;

	void AddPos(const FVector2d& InPos);
	GameAI::FVector2d GetRotation() const;
	void SetRotation(const GameAI::FVector2d& InUpdateRotation);
};
