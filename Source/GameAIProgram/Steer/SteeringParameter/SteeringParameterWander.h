#pragma once
#include "SteeringParameterBase.h"

#include "SteeringParameterWander.generated.h"

UCLASS(editinlinenew)
class USteeringParameterWander : public USteeringParameterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	double WanderRadius;

	UPROPERTY(EditAnywhere)
	double WanderDistance;

	UPROPERTY(EditAnywhere)
	double WanderJitter;
};
