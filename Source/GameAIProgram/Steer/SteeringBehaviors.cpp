#include "SteeringBehaviors.h"

#include "Calculator/Calculator.h"
#include "Vehicle/Vehicle.h"
#include "Steer/SteeringParameter/SteeringParameterWander.h"

#define GET_STEERING_PARAM(BehaviorTypeName) \
USteeringParameter##BehaviorTypeName##* FSteeringBehaviors::GetSteeringParam##BehaviorTypeName##() const\
{\
	if (GetSteeringTarget().IsValid() == false)\
		return nullptr;\
	return GetSteeringTarget()->GetSteeringParam<USteeringParameter##BehaviorTypeName##>(EBehaviorType::##BehaviorTypeName##);\
}

#include "SteeringParamList.inl"
#undef GET_STEERING_PARAM

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

TWeakObjectPtr<AVehicle> FSteeringBehaviors::GetSteeringTarget() const
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

const AVehicle* FSteeringBehaviors::GetTargetVehicle()
{
	return m_TargetVehicle;
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

FVector2d FSteeringBehaviors::GetTargetWander()
{
	return m_TargetWander;
}

void FSteeringBehaviors::SetTargetWander(const FVector2d& InTargetWander)
{
	m_TargetWander = InTargetWander;
}
