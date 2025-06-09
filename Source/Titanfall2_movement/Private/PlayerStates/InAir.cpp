// Copyright by Vishnu Suresh

#include "PlayerStates/InAir.h"

#include "Character/Player/TF_Player.h"
#include "Interfaces/PlayerControllerInterface.h"

void UInAir::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->SetCheckForWalls(false);
	
	FVector Direction = PlayerCharacter->GetWallNormal();
	Direction.Normalize();

	FVector LaunchVelocity = Direction * PlayerCharacter->GetJumpXForce() * 0.5f;
	PlayerCharacter->LaunchCharacter(LaunchVelocity, false, false);
}

void UInAir::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");

	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("Jump");
	}
}

void UInAir::ExitState()
{
	Super::ExitState();
	PlayerCharacter->SetCheckForWalls(true);
}


