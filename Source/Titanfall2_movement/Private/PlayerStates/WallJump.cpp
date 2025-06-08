// Copyright by Vishnu Suresh

#include "PlayerStates/WallJump.h"
#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void UWallJump::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);

	PlayerCharacter->JumpMaxCount = PlayerCharacter->GetWallJumpMaxCount();
	FVector Direction = PlayerCharacter->GetWallNormal();
	Direction.Normalize();

	FVector LaunchVelocity = Direction * PlayerCharacter->GetJumpXForce() +
		PlayerCharacter->GetActorForwardVector() * PlayerCharacter->GetJumpYForce() +
			PlayerCharacter->GetActorUpVector() * PlayerCharacter->GetJumpZForce();
	
	PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
}

void UWallJump::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	if (PlayerControllerInterface->HasJumpRequested() && PlayerCharacter->JumpCurrentCount < PlayerCharacter->JumpMaxCount)
	{
		PlayerCharacter->Jump();
	}
	if (!PlayerCharacter->GetCharacterMovement()->IsFalling())
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
}

void UWallJump::ExitState()
{
	Super::ExitState();
	PlayerCharacter->JumpMaxCount = PlayerCharacter->GetDefaultJumpMaxCount();
}
