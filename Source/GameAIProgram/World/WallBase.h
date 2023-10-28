#pragma once
#include "Define/Vector2d.h"
#include "Actor/AIActorBase.h"
#include "WallBase.generated.h"

UCLASS()
class AUWallBase : public AAIActorBase
{
	GENERATED_BODY()

public :
	AUWallBase(const FObjectInitializer& ObjectInitializer);
	
	FVector2d GetFrom() const;
	FVector2d GetTo() const;
	FVector2d GetNormal() const;
	FVector2d GetReverseNormal();
	bool IsActorInnerWall();

protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
public:
	UPROPERTY(EditAnywhere)
	float WallLength = 100.0f;
	
	UPROPERTY(EditAnywhere, Transient)
	TObjectPtr<UStaticMeshComponent> WallMesh; 
};
