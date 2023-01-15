#include "Arrive.h"

#include "Define/DebugIndexDefine.h"
#include "Vehicle/Vehicle.h"

FVector2d Arrive::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	auto Vehicle = InOwner.Pin()->GetSteeringTarget();
	FVector2d VehiclePos = Vehicle.Get()->GetPos2d();
	FVector2d TargetPos = InOwner.Pin()->GetTargetPos();
	FVector2d ToTarget = TargetPos - VehiclePos;
	double Distance = ToTarget.Length();
	if(Distance <= 0)
		return {0, 0};

	double Deceleration = static_cast<double>(Vehicle.Get()->Deceleration);
	double Speed = Distance / Deceleration * Vehicle.Get()->DecelerationTweaker;
	Speed = FMath::Min(Speed, Vehicle.Get()->GetMaxSpeed());

	FVector2d DesiredVelocity = ToTarget * Speed / Distance;

	PrintArriveDebugMessage(Speed, DesiredVelocity);
	return DesiredVelocity - Vehicle->GetVelocity2d();
}

void Arrive::PrintArriveDebugMessage(const double& InSpeed, const FVector2d& InDesiredVelocity)
{
	const FString& MessageSpeed = FString::Printf(TEXT("ArriveSpeed : (%f)"), InSpeed);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::ArriveSpeed, FDebugIndex::OnDisplayTime, FColor::Green, MessageSpeed);

	const FString& MessageVelocity = FString::Printf(TEXT("ArriveVelocity : (%f,%f)"), InDesiredVelocity.X, InDesiredVelocity.Y);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::ArriveDesiredVelocity, FDebugIndex::OnDisplayTime, FColor::Green, MessageVelocity);
}

FVector2d Arrive::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return FVector2d::Zero();
}
