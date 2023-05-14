#pragma once
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

class ISteeringBehaviorsCalculator;
class FSteeringBehaviors;

class Calculator
{
public:
	static FVector2d Calculate(TWeakPtr<FSteeringBehaviors> InCalculateTarget);
	
private:
	static FVector2d CalculateWeightedSum(TWeakPtr<FSteeringBehaviors> InCalculateTarget);
	static FVector2d CalculatePrioritized(TWeakPtr<FSteeringBehaviors> InCalculateTarget);
	static FVector2d CalculateDithered(TWeakPtr<FSteeringBehaviors> InCalculateTarget);
	static TArray<TWeakPtr<ISteeringBehaviorsCalculator>> GetOnFlagCalculateBehaviorType(TWeakPtr<FSteeringBehaviors> InCalculateTarget, TArray<int32>& InIteratorArray);
private:
	static TMap<int32, TSharedPtr<ISteeringBehaviorsCalculator>> sBehaviorsCalculatorContainer;
};
