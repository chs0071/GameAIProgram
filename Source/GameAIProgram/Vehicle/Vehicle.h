#pragma once
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

private:
	TSharedPtr<FSteeringBehaviors> m_SteeringBehaviors;
};
