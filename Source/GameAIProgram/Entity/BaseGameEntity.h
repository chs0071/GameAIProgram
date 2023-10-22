#pragma once
#include "Actor/AIActorBase.h"
#include "Define/Vector2d.h"
#include "BaseGameEntity.generated.h"

UCLASS()
class ABaseGameEntity : public AAIActorBase
{
	GENERATED_BODY()
public:
	ABaseGameEntity();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Update(float DeltaSeconds);
	
public:
	int32 GetID() const;
	bool IsTaged() const { return m_IsTag; }
	void Tag() { m_IsTag = true; }
	void UnTag() { m_IsTag = false; }

	UFUNCTION(BlueprintImplementableEvent)
	float GetBoundingRadius() const;
	
private:
	int32 m_ID;
	bool m_IsTag = false;
};
