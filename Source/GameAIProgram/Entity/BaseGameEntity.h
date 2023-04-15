#pragma once
#include "Define/Vector2d.h"
#include "BaseGameEntity.generated.h"

UCLASS()
class ABaseGameEntity : public AActor
{
	GENERATED_BODY()
public:
	ABaseGameEntity();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Update(float DeltaSeconds);
	
public:
	int32 GetID() const;
	FVector GetPos() const;
	FVector2d GetPos2d() const;
	void SetPos(const FVector& InPos);
	float GetScale() const;
	float GetBoundingRadius() const;

	void AddPos(const FVector2d& InPos);
	GameAI::FVector2d GetRotation();
	void SetRotation(const GameAI::FVector2d& InUpdateRotation);

	bool IsTaged() const { return m_IsTag; }
	void Tag() { m_IsTag = true; }
	void UnTag() { m_IsTag = false; }

private:
	UPROPERTY()
	Sp
	
private:
	int32 m_ID;
	float m_BoundingRadius = 0.0f; // to do... 값 넣어야함
	bool m_IsTag = false;
};
