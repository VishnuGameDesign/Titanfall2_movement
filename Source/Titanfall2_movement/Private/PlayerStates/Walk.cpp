// Copyright by Vishnu Suresh


#include "PlayerStates/Walk.h"
#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void UWalk::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetWalkSpeed();
}

void UWalk::TickState(float DelaTime)
{
	Super::TickState(DelaTime);
	if (PlayerControllerInterface->HasCrouchRequested())
	{
		RequestStateSwitch("Crouch");
	}
	if (PlayerControllerInterface->HasSprintRequested())
	{
		RequestStateSwitch("Sprint");
	}
	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("Jump");
	}
	if (!IsPlayerMoving())
	{
		RequestStateSwitch("Idle");
	}
}
