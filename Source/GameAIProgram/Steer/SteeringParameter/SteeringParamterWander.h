#pragma once
#include "SteeringParameterBase.h"

#include "SteeringParamterWander.generated.h"

UCLASS(editinlinenew)
class USteeringParamterWander : public USteeringParameterBase
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
