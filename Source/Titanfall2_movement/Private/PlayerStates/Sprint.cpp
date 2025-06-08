// Copyright by Vishnu Suresh


#include "PlayerStates/Sprint.h"
#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void USprint::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetSprintSpeed();
}

void USprint::TickState(float DelaTime)
{
	Super::TickState(DelaTime);
	if (PlayerControllerInterface->HasSprintRequested() == false)
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("Jump");
	}
	if (PlayerControllerInterface->HasCrouchRequested())
	{
		RequestStateSwitch("Slide");
	}
}

void USprint::ExitState()
{
	Super::ExitState();
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetWalkSpeed();
}
