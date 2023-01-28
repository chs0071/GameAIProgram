#include "Pursuit.h"

#include "Seek.h"
#include "Define/GameAILog.h"
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
	const FVector2D& LocalEvaderHeadingDirection = LocalEvader->GetHeadingDirection();

	Seek LocalSeek;
	if(CheckUseSeek(LocalToEvader, LocalOwnerHeadingDirection, LocalEvaderHeadingDirection))
	{
		AI_LOG(FDebugIndex::PursuitResult, TEXT("Call Seek"))
		return LocalSeek.Execute(InOwner);
	}
	
	const double LocalPredictedSpeed = (LocalOwnerVehicle->GetMaxSpeed() + LocalEvader->GetSpeed());
	const double LocalLookAheadTime = LocalToEvader.Length() / LocalPredictedSpeed;

	const FVector2d& LocalEvaderDeltaPosition = LocalEvader->GetVelocity2d() * LocalLookAheadTime;
	const FVector2d& LocalEvaderPredicatedPosition = LocalEvaderPos + LocalEvaderDeltaPosition;

	AI_LOG(FDebugIndex::PursuitResult, TEXT("Call Predicated Seek"))
	return LocalSeek.Execute(InOwner, LocalEvaderPredicatedPosition);
}

FVector2d Pursuit::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}

bool Pursuit::CheckUseSeek(const FVector2d& InToEvader, const FVector2D& InOwnerHeadingDirection, const FVector2D& InEvaderHeadingDirection)
{
	AI_LOG(FDebugIndex::PursuitOwnerHeadingDirection, TEXT("OwnerHeading : x : %f, y : %f"), InOwnerHeadingDirection.X, InOwnerHeadingDirection.Y)
	AI_LOG(FDebugIndex::PursuitEvaderHeadingDirection, TEXT("EvaderHeading : x : %f, y : %f"), InEvaderHeadingDirection.X, InEvaderHeadingDirection.Y)

	const double LocalRelativeHeading = InOwnerHeadingDirection.Dot(InEvaderHeadingDirection);
	const bool LocalIsEvaderToFront = InToEvader.Dot(InOwnerHeadingDirection) > 0;
	const bool LocalIsValidDirection = LocalRelativeHeading > 0.95;

	AI_LOG(FDebugIndex::PursuitRelativeHeading, TEXT("RelativeHeading : %f"), LocalRelativeHeading)

	return LocalIsEvaderToFront && LocalIsValidDirection;
}