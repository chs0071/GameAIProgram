#pragma once
#include "BaseGameEntity.h"
#include "Define/Vector2d.h"

#include "MovingEntity.generated.h"

UCLASS()
class AMovingEntity : public ABaseGameEntity
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Update(float DeltaSeconds) override;
	FVector2d GetVelocity2d() const;
	void SetVelocity(FVector2d InValue);
	FVector2d GetHeadingDirection() const;
	FVector2d GetSideDirection() const;
	float GetMass() const;
	float GetMaxSpeed() const;
	float GetMaxForce() const;
	float GetMaxTurnRate() const;
	double GetSpeed() const;
	double GetSpeedSq() const;
	
public:
	UPROPERTY(EditAnywhere)
	float Mass = 1.0f;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float MaxForce = 1.0f;
	UPROPERTY(EditAnywhere)
	float MaxTurnRate = .0f;

protected:
	GameAI::FVector2d m_Velocity;
	GameAI::FVector2d m_HeadingDirection;
	GameAI::FVector2d m_SideDirection;
};
