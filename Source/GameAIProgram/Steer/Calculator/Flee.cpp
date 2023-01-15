#include "Flee.h"
#include "Vehicle/Vehicle.h"

FVector2d Flee::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	TWeakObjectPtr<AVehicle> Vehicle = InOwner.Pin()->GetSteeringTarget();

	// 달아나는 범위 거리
	const double PaintDistanceSq = 100.0 * 100.0;
	FVector2d VehiclePos = Vehicle.Get()->GetPos2d();
	FVector2d TargetPos = InOwner.Pin()->GetTargetPos();

	// 타겟하고 거리가 범위를 벗어나면 달아나기 중지
	auto FleeDistance = FVector2d::DistSquared(VehiclePos, TargetPos);
	if (FleeDistance > PaintDistanceSq)
		return {0, 0};
	
	FVector2d DestPos = VehiclePos - TargetPos;
	DestPos.Normalize();
	FVector2d DesiredVelocity = DestPos * Vehicle->GetMaxSpeed();

	return DesiredVelocity - Vehicle->GetVelocity2d();
}

FVector2d Flee::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}
