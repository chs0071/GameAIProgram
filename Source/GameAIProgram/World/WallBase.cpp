#include "WallBase.h"

AUWallBase::AUWallBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMeshComponent"));
	if (WallMesh)
	{
		WallMesh->SetIsVisualizationComponent(true);
	}
}

FVector2d AUWallBase::GetFrom() const
{
	float WallLengthHalf = WallLength / 2;
	const FVector2d& From = GetPos2d();
	const FVector2d& FromDirection = GetRotation() * -1;
	const FVector2d& Result = From + FromDirection * WallLengthHalf;
	return Result;
}

FVector2d AUWallBase::GetTo() const
{
	float WallLengthHalf = WallLength / 2;
	const FVector2d& From = GetPos2d();
	const FVector2d& ToDirection = GetRotation();
	const FVector2d& Result = From + ToDirection * WallLengthHalf;
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
		FVector Scale = WallMesh->GetRelativeScale3D();
		Scale.X = WallLength * 0.01f;
		WallMesh->SetRelativeScale3D(Scale);
	}

}
