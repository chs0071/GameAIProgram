#include "AIActorBase.h"

FVector AAIActorBase::GetPos() const
{
	return GetActorLocation();
}

FVector2d AAIActorBase::GetPos2d() const
{
	const GameAI::FVector2d& Result = GetPos();
	return Result;
}

void AAIActorBase::SetPos(const FVector& InPos)
{
	SetActorLocation(InPos);
}

float AAIActorBase::GetScale() const
{
	return 1.0f;
}

void AAIActorBase::AddPos(const FVector2d& InPos)
{
	FVector AddLocation;
	AddLocation.X = InPos.X;
	AddLocation.Y = InPos.Y;
	SetPos(GetPos() + AddLocation);
}

GameAI::FVector2d AAIActorBase::GetRotation() const
{
	return GetActorRotation();
}

void AAIActorBase::SetRotation(const GameAI::FVector2d & InUpdateRotation)
{
	GameAI::FVector2d LocalCurRotation = GetActorRotation();
	GameAI::FVector2d LocalDeltaRotation = InUpdateRotation - LocalCurRotation;
	LocalCurRotation += LocalDeltaRotation;
	SetActorRotation(LocalCurRotation);
}