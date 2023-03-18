#pragma once
#include "Define/SteeringBehaviorsDefine.h"
#include "Entity/MovingEntity.h"
#include "Vehicle.generated.h"

class FSteeringBehaviors;
class USteeringParameterBase;

UCLASS()
class AVehicle : public AMovingEntity
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Update(float DeltaSeconds) override;

	TWeakPtr<FSteeringBehaviors> GetSteeringBehaviors();
	
	USteeringParameterBase* GetSteeringParameter(const EBehaviorType& InType) const;

	template<typename ReturnType>
	ReturnType* TGetSteeringParameter(const EBehaviorType& InType) const
	{
		return Cast<ReturnType>(GetSteeringParameter(InType));
	}
	
private:
	void PrintVelocityDebugMessage();
	void PrintToTargetDistance();
	
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EBehaviorType"))
	int32 BehaviorType;

	UPROPERTY(EditAnywhere)
	TMap<EBehaviorType, TObjectPtr<USteeringParameterBase>> SteeringParams;

	UPROPERTY(EditAnywhere)
	ESummingMethod SummingMethod;

	UPROPERTY(EditAnywhere)
	EDeceleration Deceleration;

	UPROPERTY(EditAnywhere)
	double DecelerationTweaker = 0.3;

	UPROPERTY(EditAnywhere)
	FName FollowTarget;
	
private:
	TSharedPtr<FSteeringBehaviors> m_SteeringBehaviors;
};
