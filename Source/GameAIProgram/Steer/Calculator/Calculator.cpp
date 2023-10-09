#include "Calculator.h"

#include "Arrive.h"
#include "Evade.h"
#include "Define/Vector2d.h"
#include "Steer/SteeringBehaviors.h"
#include "ISteeringBehaviorsCalculator.h"
#include "Seek.h"
#include "Flee.h"
#include "ObstacleAvoidance.h"
#include "Pursuit.h"
#include "Wander.h"

TMap<int32, TSharedPtr<ISteeringBehaviorsCalculator>> Calculator::sBehaviorsCalculatorContainer =
	{
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Seek), MakeShareable(new Seek())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Flee), MakeShareable(new Flee())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Arrive), MakeShareable(new Arrive())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Pursuit), MakeShareable(new Pursuit())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Evade), MakeShareable(new Evade())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Wander), MakeShareable(new Wander())),
		TPair<int32, TSharedPtr<ISteeringBehaviorsCalculator>>(static_cast<int32>(EBehaviorType::Obstacle_Avoidance), MakeShareable(new ObstacleAvoidance())),
	};

FVector2d Calculator::Calculate(const TWeakPtr<FSteeringBehaviors>& InCalculateTarget)
{
	GameAI::FVector2d LocalSteeringForce{};
	if (InCalculateTarget.IsValid() == false)
		return LocalSteeringForce;
	 
	switch(InCalculateTarget.Pin()->GetSummingMethodType())
	{
	case ESummingMethod::Weighted_Average:
		LocalSteeringForce = CalculateWeightedSum(InCalculateTarget);
		break;
	case ESummingMethod::Prioritized:
		LocalSteeringForce = CalculatePrioritized(InCalculateTarget);
		break;
	case ESummingMethod::Dithered:
		LocalSteeringForce = CalculateDithered(InCalculateTarget);
		break;
	}
	
	return LocalSteeringForce;
}

FVector2d Calculator::CalculateWeightedSum(const TWeakPtr<FSteeringBehaviors>& InCalculateTarget)
{
	FVector2d Result;

	static TArray<int32> IteratorArray{
		static_cast<int32>(EBehaviorType::Wall_Avoidance),
		static_cast<int32>(EBehaviorType::Obstacle_Avoidance),
		static_cast<int32>(EBehaviorType::Evade),
		static_cast<int32>(EBehaviorType::Separation),
		static_cast<int32>(EBehaviorType::Allignment),
		static_cast<int32>(EBehaviorType::Cohesion),
		static_cast<int32>(EBehaviorType::Wander),
		static_cast<int32>(EBehaviorType::Seek),
		static_cast<int32>(EBehaviorType::Flee),
		static_cast<int32>(EBehaviorType::Arrive),
		static_cast<int32>(EBehaviorType::Pursuit),
		static_cast<int32>(EBehaviorType::OffsetPursuit),
		static_cast<int32>(EBehaviorType::Interpose),
		static_cast<int32>(EBehaviorType::Hide),
		static_cast<int32>(EBehaviorType::FollowPath),
		};
	
	const auto& OnFlagCalculateBehaviorType = GetOnFlagCalculateBehaviorType(InCalculateTarget, IteratorArray);
	for (const auto& Element : OnFlagCalculateBehaviorType)
	{
		Result += Element.Pin()->Execute(InCalculateTarget) * Element.Pin()->GetWeight();
	}
	
	return Result;
}

FVector2d Calculator::CalculatePrioritized(TWeakPtr<FSteeringBehaviors> InCalculateTarget)
{
	// todo... 나중에 사용할 때 이넘문 순서를 정리해야한다.
	static TArray<int32> IteratorArray{
		static_cast<int32>(EBehaviorType::Seek),
		static_cast<int32>(EBehaviorType::Flee),
		static_cast<int32>(EBehaviorType::Arrive),
		static_cast<int32>(EBehaviorType::Wander),
		static_cast<int32>(EBehaviorType::Cohesion),
		static_cast<int32>(EBehaviorType::Separation),
		static_cast<int32>(EBehaviorType::Allignment),
		static_cast<int32>(EBehaviorType::Obstacle_Avoidance),
		static_cast<int32>(EBehaviorType::Wall_Avoidance),
		static_cast<int32>(EBehaviorType::FollowPath),
		static_cast<int32>(EBehaviorType::Pursuit),
		static_cast<int32>(EBehaviorType::Evade),
		static_cast<int32>(EBehaviorType::Interpose),
		static_cast<int32>(EBehaviorType::Hide),
		static_cast<int32>(EBehaviorType::Flock),
		static_cast<int32>(EBehaviorType::OffsetPursuit),
		};

	const FVector2d Result;
	return Result;
}

FVector2d Calculator::CalculateDithered(TWeakPtr<FSteeringBehaviors> InCalculateTarget)
{
	// todo... 나중에 사용할 때 이넘문 순서를 정리해야한다.
	static TArray<int32> IteratorArray{
		static_cast<int32>(EBehaviorType::Seek),
		static_cast<int32>(EBehaviorType::Flee),
		static_cast<int32>(EBehaviorType::Arrive),
		static_cast<int32>(EBehaviorType::Wander),
		static_cast<int32>(EBehaviorType::Cohesion),
		static_cast<int32>(EBehaviorType::Separation),
		static_cast<int32>(EBehaviorType::Allignment),
		static_cast<int32>(EBehaviorType::Obstacle_Avoidance),
		static_cast<int32>(EBehaviorType::Wall_Avoidance),
		static_cast<int32>(EBehaviorType::FollowPath),
		static_cast<int32>(EBehaviorType::Pursuit),
		static_cast<int32>(EBehaviorType::Evade),
		static_cast<int32>(EBehaviorType::Interpose),
		static_cast<int32>(EBehaviorType::Hide),
		static_cast<int32>(EBehaviorType::Flock),
		static_cast<int32>(EBehaviorType::OffsetPursuit),
		};

	const FVector2d Result;
	return Result;
}

TArray<TWeakPtr<ISteeringBehaviorsCalculator>> Calculator::GetOnFlagCalculateBehaviorType(const TWeakPtr<FSteeringBehaviors>& InCalculateTarget, TArray<int32>& InIteratorArray)
{
	TArray<TWeakPtr<ISteeringBehaviorsCalculator>> Result;

	for (const int32& Element : InIteratorArray)
	{
		if (InCalculateTarget.Pin()->OnBehaviorCalculateFlag(Element))
		{
			const auto BehaviorsCalculatorPtr = sBehaviorsCalculatorContainer.Find(Element);

			if (BehaviorsCalculatorPtr == nullptr)
				continue;
			
			Result.Add(*BehaviorsCalculatorPtr);
		}
	}
	return Result;
}
