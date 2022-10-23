#include "Seek.h"

#include "Vehicle/Vehicle.h"

FVector2d Seek::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	TWeakObjectPtr<AVehicle> Vehicle = InOwner.Pin()->GetSteeringTarget();
	FVector2d TargetPos = InOwner.Pin()->GetTargetPos();
	FVector2d DestPos = TargetPos - Vehicle.Get()->GetPos2d();
	DestPos.Normalize();
	FVector2d DesiredVelocity = DestPos * Vehicle->GetMaxSpeed();

	return DesiredVelocity - Vehicle->GetVelocity2d();
}
