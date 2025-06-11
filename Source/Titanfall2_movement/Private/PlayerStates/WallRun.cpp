
// Copyright by Vishnu Suresh

#include "PlayerStates/WallRun.h"
#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void UWallRun::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->SetIsRunningOnWall(true);
}

void UWallRun::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	if (PlayerCharacter->GetWallDetected())
	{
		PlayerCharacter->bUseControllerRotationYaw = false;
		PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		
		const FVector LaunchVelocity = FVector::CrossProduct(PlayerCharacter->GetWallNormal(),
			PlayerCharacter->GetActorUpVector()) * PlayerCharacter->GetWallRunSpeed() * PlayerCharacter->GetFacingDirection();

		PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
	else
	{
		IsPlayerMoving() ? RequestStateSwitch("Idle") : RequestStateSwitch("Walk");
	}

	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("WallJump");
	}
}

void UWallRun::ExitState()
{
	Super::ExitState();
	PlayerCharacter->bUseControllerRotationYaw = true;
	PlayerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	PlayerCharacter->SetIsRunningOnWall(false);
}


