#pragma once
#include "Define/SteeringBehaviorsDefine.h"
#include "Entity/MovingEntity.h"
#include "Vehicle.generated.h"

class FSteeringBehaviors;

UCLASS()
class AVehicle : public AMovingEntity
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Update(float DeltaSeconds) override;

	TWeakPtr<FSteeringBehaviors> GetSteeringBehaviors();
private:
	void PrintVelocityDebugMessage();
	void PrintToTargetDistance();
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EBehaviorType"))
	int32 BehaviorType;

	UPROPERTY(EditAnywhere)
	ESummingMethod SummingMethod;

	UPROPERTY(EditAnywhere)
	EDeceleration Deceleration;

	UPROPERTY(EditAnywhere)
	double DecelerationTweaker = 0.3;
	
private:
	TSharedPtr<FSteeringBehaviors> m_SteeringBehaviors;
};
