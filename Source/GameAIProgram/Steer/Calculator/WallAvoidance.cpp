#include "WallAvoidance.h"

#include "Define/AIMath.h"
#include "Vehicle/Vehicle.h"
#include "World/GameAILevelScript.h"
#include "World/WallBase.h"

FVector2d WallAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner)
{
	CreateFeelers(InOwner);

	double CurrentNearDistance = 0.f;
	double NearestDistance = TNumericLimits<double>::Max();

	FVector2d SteeringForce, CurCrossingPoint, LastCrossingPoint;
	
	TWeakObjectPtr<AVehicle> LocalVehicle = InOwner.Pin()->GetSteeringTarget();
	const auto LocalVehicleWorld = LocalVehicle.Get()->GetWorld();
	const auto LocalLevelScriptActor = LocalVehicleWorld->GetLevelScriptActor();
	const AGameAILevelScript* LocalLevelScript = Cast<AGameAILevelScript>(LocalLevelScriptActor);
	const FVector2d& VehiclePos = LocalVehicle->GetPos2d();
	TWeakObjectPtr<const AUWallBase> LocalNearestWall;
	
	const TArray<AUWallBase*>& LocalWalls = LocalLevelScript->GetWalls();
	for (const FVector2d& LocalFeelerDirection : m_Feelers)
	{
		for (const AUWallBase* LocalWall : LocalWalls)
		{
			bool IsLineIntersection = LineIntersection(VehiclePos, LocalFeelerDirection,
				LocalWall->GetFrom(), LocalWall->GetTo(),
				CurrentNearDistance, CurCrossingPoint);
			if (IsLineIntersection == false)
				continue;
			if (NearestDistance < CurrentNearDistance)
				continue;
			LocalNearestWall = LocalWall;
			NearestDistance = CurrentNearDistance;
			LastCrossingPoint = CurCrossingPoint;
		}

		if (LocalNearestWall.IsValid())
		{
			FVector2d OverShoot = LocalFeelerDirection - LastCrossingPoint;

			SteeringForce = LocalNearestWall.Get()->GetNormal() * OverShoot.Length();
		}
	}

	return SteeringForce;
}

FVector2d WallAvoidance::Execute(TWeakPtr<FSteeringBehaviors> InOwner, const GameAI::FVector2d& InTargetPos)
{
	return {};
}

void WallAvoidance::CreateFeelers(TWeakPtr<FSteeringBehaviors> InOwner)
{
	m_Feelers.Empty();
	
	TWeakObjectPtr<AVehicle> Vehicle = InOwner.Pin()->GetSteeringTarget();
	FVector2d LocalFeelerDirection_Center = m_FeelerLength * Vehicle.Get()->GetHeadingDirection();
	m_Feelers.Emplace(LocalFeelerDirection_Center);

	FVector2d LocalHeadingDirection = Vehicle.Get()->GetHeadingDirection();
	float LeftFeelerRad = TWO_PI - AI_Math::QuaterPI;
	FVector2d LeftFeelerDirection = CalculateFeelerDirection(LocalHeadingDirection, LeftFeelerRad);

	float RightFeelerRad = AI_Math::QuaterPI;
	FVector2d RightFeelerDirection = CalculateFeelerDirection(LocalHeadingDirection, RightFeelerRad);
	
	FVector2d LocalFeelerDirection_Left = m_FeelerLength / 2 * LeftFeelerDirection;
	FVector2d LocalFeelerDirection_Right = m_FeelerLength / 2 * RightFeelerDirection;
	m_Feelers.Emplace(LocalFeelerDirection_Left);
	m_Feelers.Emplace(LocalFeelerDirection_Right);
}

FVector2d WallAvoidance::CalculateFeelerDirection(const FVector2d& InDirection, float InRadian)
{
	float LocalFeelerDeg = FMath::RadiansToDegrees(InRadian);
	FVector2d Result = InDirection.GetRotated(LocalFeelerDeg);
	return Result;
}

bool WallAvoidance::LineIntersection(const FVector2d& InFeelerPointA, const FVector2d& InFeelerPointB, const FVector2d& InWallPointA, const FVector2d& InWallPointB
	, double& OutDistance, FVector2d& OutAcrossPoint)
{
	double FeelerTiltNumerator = (InFeelerPointA.Y - InWallPointA.Y) * (InWallPointB.X * InWallPointA.X) - (InFeelerPointA.X - InWallPointA.X) * (InWallPointB.Y - InWallPointA.X);
	double TiltDenominator = (InFeelerPointB.X - InFeelerPointA.X) * (InWallPointB.Y - InWallPointA.Y) - (InFeelerPointB.Y - InWallPointA.Y) * (InWallPointB.X - InWallPointA.X);
	
	double WallTiltNumerator = (InFeelerPointA.Y - InWallPointA.Y) * (InFeelerPointB.X * InFeelerPointA.X) - (InFeelerPointA.X - InWallPointA.X) * (InFeelerPointB.Y - InFeelerPointA.Y);
	
	if (TiltDenominator == 0)
		return false;

	double FeelerTilt = FeelerTiltNumerator / TiltDenominator;
	double WallTilt = WallTiltNumerator / TiltDenominator;

	if (FeelerTilt > 0 && FeelerTilt < 1 && WallTilt > 0 && WallTilt < 1)
	{
		OutDistance = FVector2d::Distance(InFeelerPointA, InFeelerPointB) * FeelerTilt;
		OutAcrossPoint = InFeelerPointA + FeelerTilt * (InFeelerPointB - InFeelerPointA);
		return true;
	}
	return false;
}

// 두 선분이 교차하는지 판단하는 함수
bool WallAvoidance::IsAcrossLine(const FVector2d& InFeelerPointA, const FVector2d& InFeelerPointB, const FVector2d& InWallPointA, const FVector2d& InWallPointB)
{
	int ResCCW_WallA = CounterClockWise(InFeelerPointA, InFeelerPointB, InWallPointA);
	int ResCCW_WallB = CounterClockWise(InFeelerPointA, InFeelerPointB, InWallPointB);
	int ResCCW_FeelerA = CounterClockWise(InWallPointA, InWallPointB, InFeelerPointA);
	int ResCCW_FeelerB = CounterClockWise(InWallPointA, InWallPointB, InFeelerPointB);
	
	int CCWAcrossLineFromWall = ResCCW_WallA * ResCCW_WallB;
	int CCWAcrossLineFromFeeler = ResCCW_FeelerA * ResCCW_FeelerB;

	// 동일선상에 있는지 검사
	bool IsCollinear = CCWAcrossLineFromWall == 0 && CCWAcrossLineFromFeeler == 0;
	if (IsCollinear)
	{
		const FVector2d& FeelerPointMin = FMath::Min(InFeelerPointA, InFeelerPointB);
		const FVector2d& FeelerPointMax = FMath::Max(InFeelerPointA, InFeelerPointB);
		const FVector2d& WallPointMin = FMath::Min(InWallPointA, InWallPointB);
		const FVector2d& WallPointMax = FMath::Max(InWallPointA, InWallPointB);

		return WallPointMin <= FeelerPointMax && FeelerPointMin <= WallPointMax;
	}
	bool IsAcrossLineFromWall = CCWAcrossLineFromWall <= 0;
	bool IsAcrossLineFromFeeler = CCWAcrossLineFromFeeler <= 0;

	return IsAcrossLineFromWall && IsAcrossLineFromFeeler;
}
// 선분으로부터 점이 어느방향에 위치하는지 알아내는 함수
int WallAvoidance::CounterClockWise(const FVector2d& InLinePointA, const FVector2d& InLinePointB, const FVector2d& InTargetPoint)
{
	//외적
	//S = (x1y2 + x2y3 + x3y1) - (x2y1 + x3y2 + x1y3)
	float X1 = InLinePointA.X;
	float Y1 = InLinePointA.Y;
	float X2 = InLinePointB.X;
	float Y2 = InLinePointB.Y;
	float X3 = InTargetPoint.X;
	float Y3 = InTargetPoint.Y;

	const int Result = (X1 * Y2 + X2 * Y3 + X3 * Y1) - (X2 * Y1 + X3 * Y2 + X1 * Y3);
	if (Result > 0)
		return 1;
	if (Result == 0)
		return 0;
	return -1;
}

