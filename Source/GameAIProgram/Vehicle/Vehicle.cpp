﻿#include "Vehicle.h"

#include "Steer/SteeringBehaviors.h"

void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	m_SteeringBehaviors = MakeShared<FSteeringBehaviors>(this);
}

void AVehicle::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);
	FVector2d LocalSteeringForce = m_SteeringBehaviors->Calculate();
	FVector2d LocalAcceleration = LocalSteeringForce / Mass;
	GameAI::FVector2d LocalCalVelocity = LocalAcceleration * DeltaSeconds;
	m_Velocity += LocalCalVelocity;
	m_Velocity.Truncate(MaxSpeed);
	AddPos(m_Velocity * DeltaSeconds);

	if (m_Velocity.SquaredLength() > 0.00000001)
	{
		m_HeadingDirection = m_Velocity;
		m_HeadingDirection.Normalize();
		m_SideDirection = m_HeadingDirection.Perp();
	}
}