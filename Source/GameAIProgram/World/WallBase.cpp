#include "WallBase.h"

AUWallBase::AUWallBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMeshComponent"));
	if (WallMesh)
	{
		WallMesh->SetIsVisualizationComponent(true);
		WallMesh->SetupAttachment(RootComponent);

	}
}

FVector2d AUWallBase::GetFrom() const
{
	return GetPos2d();
}

FVector2d AUWallBase::GetTo() const
{
	const FVector2d& From = GetFrom();
	const FVector2d& Forward = GetRotation();
	const FVector2d& Result = From + Forward * WallLength;
	return Result;
}

FVector2d AUWallBase::GetNormal() const
{
	const FVector2d& From = GetFrom();
	const FVector2d& To = GetTo();
	FVector2d WallForwardDirection = To - From;
	WallForwardDirection.Normalize();
	const GameAI::FVector2d& Result = WallForwardDirection;
	return Result.Perp();
}

FVector2d AUWallBase::GetReverseNormal()
{
	const FVector2d& From = GetFrom();
	const FVector2d& To = GetTo();
	FVector2d WallForwardDirection = From - To;
	WallForwardDirection.Normalize();
	const GameAI::FVector2d& Result = WallForwardDirection;
	return Result.Perp();
}

bool AUWallBase::IsActorInnerWall()
{
	return true;
}

void AUWallBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (WallMesh)
	{
		FBoxSphereBounds LocalBounds = WallMesh->Bounds;
		LocalBounds.BoxExtent.X = WallLength;
		WallMesh->Bounds = LocalBounds;
	}

}
