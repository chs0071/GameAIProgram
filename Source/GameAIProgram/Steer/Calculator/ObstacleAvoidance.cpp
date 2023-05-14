#include "ObstacleAvoidance.h"

#include "Define/GameAILog.h"
#include "Define/Matrix.h"
#include "Vehicle/Vehicle.h"
#include "World/GameAILevelScript.h"

FVector2d ObstacleAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	if(false == InOwner.IsValid())
		return FVector2d::Zero();

	TWeakObjectPtr<AVehicle> LocalVehicle = InOwner.Pin()->GetSteeringTarget();
	if(false == LocalVehicle.IsValid())
		return FVector2d::Zero();

	const auto LocalVehicleWorld = LocalVehicle.Get()->GetWorld();
	const auto LocalLevelScriptActor = LocalVehicleWorld->GetLevelScriptActor();
	const AGameAILevelScript* LocalLevelScript = Cast<AGameAILevelScript>(LocalLevelScriptActor);
	
	const TArray<ABaseGameEntity*>& LocalObstacles = LocalLevelScript->GetObtacles();

	if(LocalObstacles.IsEmpty())
		return FVector2d::Zero();

	const float LocalDetectionBoxLength = GetDetectionBoxLength(LocalVehicle);
	AI_LOG(FDebugIndex::ObstaclesDetectionBoxLength, TEXT("DetectionBoxLength : %f"), LocalDetectionBoxLength);

	TagObstaclesWithinViewRange(LocalVehicle, LocalObstacles, LocalDetectionBoxLength);

	FString LocalTagedObject = TEXT("Taged Objects : ");
	for(const auto Element : LocalObstacles)
	{
		if(Element->IsTaged())
			LocalTagedObject.Append(Element->GetActorLabel() + TEXT(", "));
	}
	
	AI_LOG(FDebugIndex::OnObstaclesTag, TEXT("%s"), *LocalTagedObject);
	
	ABaseGameEntity* LocalClosetIntersectionObstacle = GetClosetIntersectionObstacle(LocalVehicle, LocalObstacles);
	if(false == IsValid(LocalClosetIntersectionObstacle))
	{
		AI_LOG(FDebugIndex::ClosetIntersectionObstacle, TEXT("ClosetIntersectionObstacle : Not"));
		return FVector2d::Zero();
	}

	AI_LOG(FDebugIndex::ClosetIntersectionObstacle, TEXT("ClosetIntersectionObstacle : %s"), *LocalClosetIntersectionObstacle->GetActorLabel());

	const FVector2D LocalSteeringForce = GetSteeringForce(LocalVehicle, LocalClosetIntersectionObstacle, LocalDetectionBoxLength);
	const FVector2D ReturnValue = GameAI::Matrix::VectorToWorldSpace(LocalSteeringForce,
											 LocalVehicle->GetHeadingDirection(),
											 LocalVehicle->GetSideDirection());
	
	return ReturnValue;
}

FVector2d ObstacleAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return FVector2d::Zero(); 
}

float ObstacleAvoidance::GetDetectionBoxLength(TWeakObjectPtr<AVehicle>& InVehicle)
{
	if(false == InVehicle.IsValid())
		return GetMinDetectionBoxLength();

	const float LocalSpeedRate = InVehicle->GetSpeed() / InVehicle->GetMaxSpeed();
	return GetMinDetectionBoxLength() + LocalSpeedRate * GetMinDetectionBoxLength();  
}

void ObstacleAvoidance::TagObstaclesWithinViewRange(TWeakObjectPtr<AVehicle>& InVehicle, const TArray<ABaseGameEntity*>& InObstacles, const float InDetectionBoxLength)
{
	if(false == InVehicle.IsValid())
		return;
	
	for(const auto& Element : InObstacles)
	{
		if(false == IsValid(Element))
			continue;

		Element->UnTag();
		
		const FVector2d LocalDistance = InVehicle->GetPos2d() - Element->GetPos2d();

		const double LocalBoxLength = InDetectionBoxLength + Element->GetBoundingRadius();

		const bool LocalIsInViewRange = LocalDistance.SquaredLength() < LocalBoxLength * LocalBoxLength;
		if(LocalIsInViewRange)
			Element->Tag();
	}
}

ABaseGameEntity* ObstacleAvoidance::GetClosetIntersectionObstacle(TWeakObjectPtr<AVehicle>& InVehicle,
                                                                  const TArray<ABaseGameEntity*>& InObstacles)
{
	double DistToClosestIP = TNumericLimits<double>().Max();
	ABaseGameEntity* ReturnValue = nullptr;
	
	for(const auto& Element : InObstacles)
	{
		if(false == IsValid(Element))
			continue;

		if(false == Element->IsTaged())
			continue;

		const FString LocalElementName = Element->GetActorLabel();

		const FVector2D ElementToLocalPosition = GameAI::Matrix::PointToLocalSpace(Element->GetPos2d(),
		                                                                           InVehicle->GetHeadingDirection(),
		                                                                           InVehicle->GetSideDirection(),
		                                                                           InVehicle->GetPos2d());

		// X의 음수는 Vehicle의 뒤에있는 장애물이니 검사하지 않는다.
		if(ElementToLocalPosition.X < 0)
			continue;

		const float& LocalVehicleRadius = InVehicle->GetBoundingRadius();
		const float& LocalElementRadius = Element->GetBoundingRadius();
		const double LocalExpandedRadius = LocalVehicleRadius + LocalElementRadius;
		if(const bool LocalIsOverExpandRadius = FMath::Abs(ElementToLocalPosition.Y) >= LocalExpandedRadius)
		{
			continue;
		}
			

		const FVector2D LocalCircleCenter = ElementToLocalPosition;
		const double LocalDeltaAcrossPointByZeroX = FMath::Sqrt(LocalExpandedRadius * LocalExpandedRadius - LocalCircleCenter.Y * LocalCircleCenter.Y);
		double LocalCloseAcrossPoint = LocalCircleCenter.X - LocalDeltaAcrossPointByZeroX;
		if(LocalCloseAcrossPoint <= 0.0f)
			LocalCloseAcrossPoint = LocalCircleCenter.X + LocalDeltaAcrossPointByZeroX;

		if(LocalCloseAcrossPoint < DistToClosestIP)
		{
			DistToClosestIP = LocalCloseAcrossPoint;
			ReturnValue = Element;
		}
	}

	return ReturnValue;
}

FVector2D ObstacleAvoidance::GetSteeringForce(TWeakObjectPtr<AVehicle>& InVehicle, ABaseGameEntity* InClosetObstacle, const float InDetectionBoxLength)
{
	if(false == IsValid(InClosetObstacle) || false == InVehicle.IsValid())
		return FVector2D::Zero(); 
	
	const FVector2D LocalPositionOfCloset = GameAI::Matrix::PointToLocalSpace(InClosetObstacle->GetPos2d(),
											 InVehicle->GetHeadingDirection(),
											 InVehicle->GetSideDirection(),
											 InVehicle->GetPos2d());

	double LocalMultipiler = 1.0f + (InDetectionBoxLength - LocalPositionOfCloset.X) / InDetectionBoxLength;

	FVector2D LocalSteeringForce;

	LocalSteeringForce.Y = (InClosetObstacle->GetBoundingRadius() - LocalPositionOfCloset.Y) * LocalMultipiler;

	constexpr double LocalBreakWeight = 0.2f;
	LocalSteeringForce.X = (InClosetObstacle->GetBoundingRadius() - LocalPositionOfCloset.X) * LocalBreakWeight;

	return LocalSteeringForce;
}
