#include "Evade.h"

#include "Flee.h"
#include "Define/GameAILog.h"
#include "Vehicle/Vehicle.h"

FVector2d Evade::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	if(false == InOwner.IsValid())
		return FVector2D::Zero();
	
	const AVehicle* LocalPursuer = InOwner.Pin()->GetTargetVehicle();
	if(false == IsValid(LocalPursuer))
		return FVector2D::Zero();

	const FVector2D& LocalPursuerPos = LocalPursuer->GetPos2d();
	TWeakObjectPtr<AVehicle> LocalOwnerVehicle = InOwner.Pin()->GetSteeringTarget();
	if(false == LocalOwnerVehicle.IsValid())
		return FVector2d::Zero();
	
	const FVector2D& LocalToPursuer = LocalPursuerPos - LocalOwnerVehicle->GetPos2d();
	const double LocalPredictedSpeed = (LocalOwnerVehicle->GetMaxSpeed() + LocalPursuer->GetSpeed());
	const double LocalLookAheadTime = LocalToPursuer.Length() / LocalPredictedSpeed;

	const FVector2d& LocalPursuerDeltaPosition = LocalPursuer->GetVelocity2d() * LocalLookAheadTime;
	const FVector2d& LocalPursuerPredicatedPosition = LocalPursuerPos + LocalPursuerDeltaPosition;

	Flee LocalFlee;
	AI_LOG(FDebugIndex::EvadeResult, TEXT("Call Predicated Flee"))
	return LocalFlee.Execute(InOwner, LocalPursuerPredicatedPosition);
}

FVector2d Evade::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}
