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

	TWeakObjectPtr<AVehicle> GetSteeringTarget();
	FVector2d GetTargetPos();
	void SetPath();
	void SetTarget(const AVehicle* InTarget);
	void SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent);
	void SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent);
	void ResetSteeringForce();

	bool OnBehaviorCalculateFlag(int32 InBehaviorType);


private:
	TWeakObjectPtr<AVehicle> m_SteeringTarget;
	const AVehicle* m_TargetVehicle;
	TWeakObjectPtr<AVehicle> m_AgentFirst;
	TWeakObjectPtr<AVehicle> m_AgentSecond;

	GameAI::FVector2d m_SteeringForce;
};
