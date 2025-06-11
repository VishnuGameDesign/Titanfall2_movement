// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "PlayerBaseState.generated.h"

class IPlayerControllerInterface;
class ATF_Player;

UCLASS(Abstract, Blueprintable, BlueprintType)
class TITANFALL2_MOVEMENT_API UPlayerBaseState : public UStateBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATF_Player> PlayerCharacter;

	TScriptInterface<IPlayerControllerInterface> PlayerControllerInterface;

	virtual void EnterState(AActor* Owner) override;
	virtual void ExitState() override;
	virtual void TickState(float DeltaTime) override;

	virtual void HandleWalk(APawn* ControlledPawn, FVector Fwd, FVector Right, FVector2D InputAxis);

	bool IsPlayerMoving();
	bool IsPlayerSprinting();
	void RequestStateSwitch(const FString& StateName);
	void CrouchToTargetHeight(float TargetHeight, float Time);
};
