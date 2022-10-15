#include "BaseGameEntity.h"

#include "Define/Vector2d.h"

void ABaseGameEntity::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameEntity::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	const FTransform& LocalTr = GetTransform();
	return LocalTr.GetLocation();
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
