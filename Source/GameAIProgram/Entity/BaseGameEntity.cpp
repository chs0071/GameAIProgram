#include "BaseGameEntity.h"

#include "Define/Vector2d.h"

ABaseGameEntity::ABaseGameEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABaseGameEntity::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameEntity::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Update(DeltaSeconds);
}

void ABaseGameEntity::Update(float DeltaSeconds)
{
}

int32 ABaseGameEntity::GetID() const
{
	return m_ID;
}

FVector ABaseGameEntity::GetPos() const
{
	return GetActorLocation();
}

FVector2d ABaseGameEntity::GetPos2d() const
{
	const GameAI::FVector2d& Result = GetPos();
	return Result;
}

void ABaseGameEntity::SetPos(const FVector& InPos)
{
	SetActorLocation(InPos);
}

float ABaseGameEntity::GetScale() const
{
	return 1.0f;
}

float ABaseGameEntity::GetBoundingRadius() const
{
	return m_BoundingRadius;
}

void ABaseGameEntity::AddPos(const FVector2d& InPos)
{
	FVector AddLocation;
	AddLocation.X = InPos.X;
	AddLocation.Y = InPos.Y;
	SetPos(GetPos() + AddLocation);
}

GameAI::FVector2d ABaseGameEntity::GetRotation()
{
	return GetActorRotation();
}

void ABaseGameEntity::SetRotation(const GameAI::FVector2d & InUpdateRotation)
{
	GameAI::FVector2d LocalCurRotation = GetActorRotation();
	GameAI::FVector2d LocalDeltaRotation = InUpdateRotation - LocalCurRotation;
	LocalCurRotation += LocalDeltaRotation;
	SetActorRotation(LocalCurRotation);
}