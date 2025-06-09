// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/Base/PlayerBaseState.h"
#include "Idle.generated.h"

UCLASS()
class TITANFALL2_MOVEMENT_API UIdle : public UPlayerBaseState
{
	GENERATED_BODY()

protected:
	virtual void EnterState(AActor* Owner) override;
	virtual void TickState(float DelaTime) override;
};
