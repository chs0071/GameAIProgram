#pragma once

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
	static TArray<TWeakPtr<ISteeringBehaviorsCalculator>> GetOnFlagCalculateBehaviorType(TWeakPtr<FSteeringBehaviors> InCalculateTarget);
private:
	static TMap<int32, TSharedPtr<ISteeringBehaviorsCalculator>> sBehaviorsCalculatorContainer;
};
