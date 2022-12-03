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
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EBehaviorType"))
	int32 BehaviorType;

	UPROPERTY(EditAnywhere)
	ESummingMethod SummingMethod;
	
private:
	TSharedPtr<FSteeringBehaviors> m_SteeringBehaviors;
};
