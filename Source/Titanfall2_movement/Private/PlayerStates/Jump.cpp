// Copyright by Vishnu Suresh


#include "PlayerStates/Jump.h"

#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void UJump::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->Jump();
}

void UJump::TickState(float DelaTime)
{
	Super::TickState(DelaTime);
	if (PlayerControllerInterface->HasJumpRequested() && PlayerCharacter->JumpCurrentCount < PlayerCharacter->JumpMaxCount)
	{
		PlayerCharacter->Jump();
	}
	else if (!PlayerCharacter->GetCharacterMovement()->IsFalling())
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
}

void UJump::ExitState()
{
	Super::ExitState();
	PlayerCharacter->StopJumping();
}

