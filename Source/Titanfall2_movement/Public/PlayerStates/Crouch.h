// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/Base/PlayerBaseState.h"
#include "Crouch.generated.h"

UCLASS()
class TITANFALL2_MOVEMENT_API UCrouch : public UPlayerBaseState
{
	GENERATED_BODY()
protected:
	virtual void HandleWalk(APawn* ControlledPawn, FVector Fwd, FVector Right, FVector2D InputAxis) override;
	virtual void EnterState(AActor* Owner) override;
	virtual void TickState(float DeltaTime) override;
	virtual void ExitState() override;
};
