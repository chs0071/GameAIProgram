#pragma once
#include "Define/SteeringBehaviorsDefine.h"
#include "Define/Vector2d.h"

class AVehicle;

class FSteeringBehaviors : public TSharedFromThis<FSteeringBehaviors>
{
public:
	FSteeringBehaviors(const TWeakObjectPtr<AVehicle>& InSteeringTarget);

	GameAI::FVector2d Calculate();
	
	ESummingMethod GetSummingMethodType() const;
	double GetForwardRad() const;
	double GetSideRad() const;

	TWeakObjectPtr<AVehicle> GetSteeringTarget() const;
	FVector2d GetTargetPos();
	const AVehicle* GetTargetVehicle();
	void SetPath();
	void SetTarget(const AVehicle* InTarget);
	void SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent);
	void SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent);
	void ResetSteeringForce();

	bool OnBehaviorCalculateFlag(int32 InBehaviorType);

	FVector2d GetTargetWander();
	void SetTargetWander(const FVector2d& InTargetWander);

#define GET_STEERING_PARAM(BehaviorTypeName) class USteeringParameter##BehaviorTypeName##* FSteeringBehaviors::GetSteeringParam##BehaviorTypeName##() const;
#include "SteeringParamList.inl"
#undef GET_STEERING_PARAM
	
private:
	TWeakObjectPtr<AVehicle> m_SteeringTarget;
	const AVehicle* m_TargetVehicle;
	TWeakObjectPtr<AVehicle> m_AgentFirst;
	TWeakObjectPtr<AVehicle> m_AgentSecond;

	GameAI::FVector2d m_SteeringForce;

	FVector2d m_TargetWander;
};
