#pragma once
#include "Define/SteeringBehaviorsDefine.h"

class AVehicle;

class FSteeringBehaviors : public TSharedFromThis<FSteeringBehaviors>
{
public:
	FSteeringBehaviors(const TWeakObjectPtr<AVehicle>& InSteeringTarget);

	FVector2d Calculate();
	
	ESummingMethod GetSummingMethodType() const;
	double GetForwardRad() const;
	double GetSideRad() const;

	TWeakObjectPtr<AVehicle> GetSteeringTarget();
	FVector2d GetTargetPos();
	void SetPath();
	void SetTargetPos(const FVector2d& InTargetPos);
	void SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent);
	void SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent);
	void ResetSteeringForce();

	bool OnBehaviorCalculateFlag(int32 InBehaviorType);


private:
	TWeakObjectPtr<AVehicle> m_SteeringTarget;
	FVector2d m_TargetPos;
	TWeakObjectPtr<AVehicle> m_AgentFirst;
	TWeakObjectPtr<AVehicle> m_AgentSecond;

	FVector2d m_SteeringForce;
	ESummingMethod m_SummingMethodType;
	int32 m_BehaviorCalculateFlag;
};
