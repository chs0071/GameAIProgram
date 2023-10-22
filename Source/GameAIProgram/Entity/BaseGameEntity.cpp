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