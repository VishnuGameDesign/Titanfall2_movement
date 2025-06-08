// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/Base/PlayerBaseState.h"
#include "Slide.generated.h"

UCLASS()
class TITANFALL2_MOVEMENT_API USlide : public UPlayerBaseState
{
	GENERATED_BODY()
	protected:
	virtual void EnterState(AActor* Owner) override;
	virtual void TickState(float DeltaTime) override;
	virtual void ExitState() override;

private:
	float ElapsedTime = 0.0f;
	void StopSliding(float DeltaTime);
};
