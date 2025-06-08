// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/Base/PlayerBaseState.h"
#include "Walk.generated.h"

UCLASS()
class TITANFALL2_MOVEMENT_API UWalk : public UPlayerBaseState
{
	GENERATED_BODY()
protected:
	virtual void EnterState(AActor* Owner) override;
	virtual void TickState(float DelaTime) override;
};
