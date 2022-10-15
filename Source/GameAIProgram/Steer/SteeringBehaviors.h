#pragma once
class AVehicle;

class FSteeringBehaviors
{
public:
	FSteeringBehaviors(const TWeakObjectPtr<AVehicle>& InSteeringTarget);

	FVector2d Calculate();
	double GetForwardRad() const;
	double GetSideRad() const;
	
	void SetPath();
	void SetTargetPos(const FVector2d& InTargetPos);
	void SetTargetAgentFirst(const TWeakObjectPtr<AVehicle>& InAgent);
	void SetTargetAgentSecond(const TWeakObjectPtr<AVehicle>& InAgent);

private:
	TWeakObjectPtr<AVehicle> m_SteeringTarget;
	FVector2d m_TargetPos;
	TWeakObjectPtr<AVehicle> m_AgentFirst;
	TWeakObjectPtr<AVehicle> m_AgentSecond;

	FVector2d m_SteeringForce;
};
