// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/Base/PlayerBaseState.h"
#include "WallRun.generated.h"

class AController;

UCLASS()
class TITANFALL2_MOVEMENT_API UWallRun : public UPlayerBaseState
{
	GENERATED_BODY()
protected:
	virtual void EnterState(AActor* Owner) override;
	virtual void TickState(float DeltaTime) override;
	virtual void ExitState() override;

private:
	UPROPERTY()
	TObjectPtr<AController> Controller;
};
