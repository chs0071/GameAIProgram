#include "Pursuit.h"

#include "Seek.h"
#include "Define/DebugIndexDefine.h"
#include "Vehicle/Vehicle.h"

FVector2d Pursuit::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	if(false == InOwner.IsValid())
		return FVector2D::Zero();
	
	const AVehicle* LocalEvader = InOwner.Pin()->GetTargetVehicle();
	if(false == IsValid(LocalEvader))
		return FVector2D::Zero();

	const FVector2D& LocalEvaderPos = LocalEvader->GetPos2d();

	TWeakObjectPtr<AVehicle> LocalOwnerVehicle = InOwner.Pin()->GetSteeringTarget();
	if(false == LocalOwnerVehicle.IsValid())
		return FVector2d::Zero();
	
	const FVector2D& LocalOwnerPos = LocalOwnerVehicle->GetPos2d();
	const FVector2D& LocalToEvader = LocalEvaderPos - LocalOwnerPos;

	const FVector2D& LocalOwnerHeadingDirection = LocalOwnerVehicle->GetHeadingDirection();
	const FString& MessagePursuitOwnerHeadingDirection = FString::Printf(TEXT("OwnerHeading : x : %f, y : %f"), LocalOwnerHeadingDirection.X, LocalOwnerHeadingDirection.Y);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::PursuitOwnerHeadingDirection, FDebugIndex::OnDisplayTime, FColor::Green, MessagePursuitOwnerHeadingDirection);
	
	const FVector2D& LocalEvaderHeadingDirection = LocalEvader->GetHeadingDirection();
	const FString& MessagePursuitEvaderHeadingDirection = FString::Printf(TEXT("EvaderHeading : x : %f, y : %f"), LocalEvaderHeadingDirection.X, LocalEvaderHeadingDirection.Y);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::PursuitEvaderHeadingDirection, FDebugIndex::OnDisplayTime, FColor::Green, MessagePursuitEvaderHeadingDirection);
	
	const double LocalRelativeHeading = LocalOwnerHeadingDirection.Dot(LocalEvaderHeadingDirection);

	const bool LocalIsEvaderToFront = LocalToEvader.Dot(LocalOwnerVehicle->GetHeadingDirection()) > 0;
	const bool LocalIsValidDirection = LocalRelativeHeading > 0.95;

	const FString& MessagePursuitRelativeHeading = FString::Printf(TEXT("RelativeHeading : %f"), LocalRelativeHeading);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::PursuitRelativeHeading, FDebugIndex::OnDisplayTime, FColor::Green, MessagePursuitRelativeHeading);
	
	Seek LocalSeek;
	if(LocalIsEvaderToFront && LocalIsValidDirection)
	{
		const FString& Message = FString::Printf(TEXT("Call Seek"));
		GEngine->AddOnScreenDebugMessage(FDebugIndex::PursuitResult, FDebugIndex::OnDisplayTime, FColor::Green, Message);

		return LocalSeek.Execute(InOwner);
	}
	
	const double LocalPredictedSpeed = (LocalOwnerVehicle->GetMaxSpeed() + LocalEvader->GetSpeed());
	const double LocalLookAheadTime = LocalToEvader.Length() / LocalPredictedSpeed;

	const FVector2d& LocalEvaderDeltaPosition = LocalEvader->GetVelocity2d() * LocalLookAheadTime;
	const FVector2d& LocalEvaderPredicatedPosition = LocalEvaderPos + LocalEvaderDeltaPosition;

	const FString& Message = FString::Printf(TEXT("Call Predicated Seek"));
	GEngine->AddOnScreenDebugMessage(FDebugIndex::PursuitResult, FDebugIndex::OnDisplayTime, FColor::Green, Message);
	return LocalSeek.Execute(InOwner, LocalEvaderPredicatedPosition);
}

FVector2d Pursuit::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}
