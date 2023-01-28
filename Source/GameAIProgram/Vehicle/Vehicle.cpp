#include "Vehicle.h"

#include "Define/DebugIndexDefine.h"
#include "Define/WorldDefine.h"
#include "Steer/SteeringBehaviors.h"

void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	m_SteeringBehaviors = MakeShareable<FSteeringBehaviors>(new FSteeringBehaviors(this));
}

void AVehicle::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);
	
	FVector2d LocalSteeringForce = m_SteeringBehaviors->Calculate();
	FVector2d LocalAcceleration = LocalSteeringForce / Mass;
	GameAI::FVector2d LocalCalVelocity = LocalAcceleration * DeltaSeconds;
	
	m_Velocity += LocalCalVelocity;
	m_Velocity.Truncate(MaxSpeed);
	PrintVelocityDebugMessage();
	PrintToTargetDistance();
	AddPos(m_Velocity * DeltaSeconds);

	if (m_Velocity.SquaredLength() > 0.00000001)
	{
		m_HeadingDirection = m_Velocity;
		m_HeadingDirection.Normalize();
		m_SideDirection = m_HeadingDirection.Perp();
		SetRotation(m_HeadingDirection);
	}

	GameAI::FVector2d LocalCurPos = GetPos2d();
	GameAI::FVector2d::WrapAround(LocalCurPos, AI_World::MAX_SIZE.X, AI_World::MAX_SIZE.Y);
	SetPos(LocalCurPos);
}

TWeakPtr<FSteeringBehaviors> AVehicle::GetSteeringBehaviors()
{
	return m_SteeringBehaviors;
}

USteeringParameterBase* AVehicle::GetSteeringParamter(const EBehaviorType& InType) const
{
	const TObjectPtr<USteeringParameterBase>* LocalFindParameter = SteeringParams.Find(InType);
	if(nullptr == LocalFindParameter)
		return nullptr;

	return LocalFindParameter->Get();
}

void AVehicle::PrintVelocityDebugMessage()
{
	const FString& Message = FString::Printf(TEXT("Velocity : (%f,%f)"), m_Velocity.X, m_Velocity.Y);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::VehicleVelocity, FDebugIndex::OnDisplayTime, FColor::Green, Message);
}

void AVehicle::PrintToTargetDistance()
{
	const FVector2d& ToTarget = m_SteeringBehaviors->GetTargetPos() - GetPos2d();
	const double& Distance = ToTarget.Length();
	const FString& Message = FString::Printf(TEXT("Distance : (%f)"), Distance);
	GEngine->AddOnScreenDebugMessage(FDebugIndex::VehicleToTargetDistance, FDebugIndex::OnDisplayTime, FColor::Green, Message);
}
