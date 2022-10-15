#include "SteeringBehaviors.h"

#include "Define/Vector2d.h"
#include "Vehicle/Vehicle.h"


FSteeringBehaviors::FSteeringBehaviors(const TWeakObjectPtr<AVehicle>& InSteeringTarget)
	: m_SteeringTarget(InSteeringTarget)
{
	
}

FVector2d FSteeringBehaviors::Calculate()
{
	FVector2d Result;
	return Result;
}

double FSteeringBehaviors::GetForwardRad() const
{
	return m_SteeringTarget->GetHeadingDirection().Dot(m_SteeringForce);
}

double FSteeringBehaviors::GetSideRad() const
{
	return m_SteeringTarget->GetSideDirection().Dot(m_SteeringForce);
}

void FSteeringBehaviors::SetPath()
{
}

void FSteeringBehaviors::SetTargetPos(const FVector2d& InTargetPos)
{
	m_TargetPos = InTargetPos;
}

void FSteeringBehaviors::SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent)
{
	m_AgentFirst = InAgent;
}

void FSteeringBehaviors::SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent)
{
	m_AgentSecond = InAgent;
}
