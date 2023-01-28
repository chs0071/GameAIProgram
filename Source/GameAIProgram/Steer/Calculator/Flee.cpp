#include "Flee.h"
#include "Vehicle/Vehicle.h"

FVector2d Flee::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	const FVector2d& TargetPos = InOwner.Pin()->GetTargetPos();
	
	return Execute(InOwner, TargetPos);
}

FVector2d Flee::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	TWeakObjectPtr<AVehicle> Vehicle = InOwner.Pin()->GetSteeringTarget();

	// 달아나는 범위 거리
	const double PaintDistanceSq = 10000.0 * 10000.0;
	const FVector2d& VehiclePos = Vehicle.Get()->GetPos2d();

	// 타겟하고 거리가 범위를 벗어나면 달아나기 중지
	auto FleeDistance = FVector2d::DistSquared(VehiclePos, InTargetPos);
	if (FleeDistance > PaintDistanceSq)
		return {0, 0};
	
	FVector2d DestPos = VehiclePos - InTargetPos;
	DestPos.Normalize();
	const FVector2d& DesiredVelocity = DestPos * Vehicle->GetMaxSpeed();

	return DesiredVelocity - Vehicle->GetVelocity2d();
}
