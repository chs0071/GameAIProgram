#include "MovingEntity.h"

void AMovingEntity::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);
}

FVector2d AMovingEntity::GetVelocity2d() const
{
	return m_Velocity;
}

void AMovingEntity::SetVelocity(FVector2d InValue)
{
	m_Velocity = InValue;
}

FVector2d AMovingEntity::GetHeadingDirection() const
{
	return m_HeadingDirection;
}

FVector2d AMovingEntity::GetSideDirection() const
{
	return m_SideDirection;
}

float AMovingEntity::GetMass() const
{
	return Mass;
}

float AMovingEntity::GetMaxSpeed() const
{
	return MaxSpeed;
}

float AMovingEntity::GetMaxForce() const
{
	return MaxForce;
}

float AMovingEntity::GetMaxTurnRate() const
{
	return MaxTurnRate;
}
