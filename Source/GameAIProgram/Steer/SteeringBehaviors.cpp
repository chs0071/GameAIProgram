#include "SteeringBehaviors.h"

#include "Calculator/Calculator.h"
#include "Vehicle/Vehicle.h"


FSteeringBehaviors::FSteeringBehaviors(const TWeakObjectPtr<AVehicle>& InSteeringTarget)
	: m_SteeringTarget(InSteeringTarget)
	, m_TargetVehicle(nullptr)
{
}

GameAI::FVector2d FSteeringBehaviors::Calculate()
{
	m_SteeringForce = Calculator::Calculate(AsShared());

	return m_SteeringForce;
}

ESummingMethod FSteeringBehaviors::GetSummingMethodType() const
{
	return m_SteeringTarget->SummingMethod;
}

double FSteeringBehaviors::GetForwardRad() const
{
	return m_SteeringTarget->GetHeadingDirection().Dot(m_SteeringForce);
}

double FSteeringBehaviors::GetSideRad() const
{
	return m_SteeringTarget->GetSideDirection().Dot(m_SteeringForce);
}

TWeakObjectPtr<AVehicle> FSteeringBehaviors::GetSteeringTarget()
{
	return m_SteeringTarget;
}

FVector2d FSteeringBehaviors::GetTargetPos()
{
	GameAI::FVector2d ReturnValue;
	
	if(IsValid(m_TargetVehicle))
		ReturnValue = m_TargetVehicle->GetActorLocation(); 

	return ReturnValue;
}

void FSteeringBehaviors::SetPath()
{
}

void FSteeringBehaviors::SetTarget(const AVehicle* InTarget)
{
	m_TargetVehicle = InTarget;
}

void FSteeringBehaviors::SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent)
{
	m_AgentFirst = InAgent;
}

void FSteeringBehaviors::SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent)
{
	m_AgentSecond = InAgent;
}

void FSteeringBehaviors::ResetSteeringForce()
{
	m_SteeringForce = FVector2d::Zero();
}

bool FSteeringBehaviors::OnBehaviorCalculateFlag(int32 InBehaviorType)
{
	return (m_SteeringTarget->BehaviorType & InBehaviorType) == InBehaviorType;
}
