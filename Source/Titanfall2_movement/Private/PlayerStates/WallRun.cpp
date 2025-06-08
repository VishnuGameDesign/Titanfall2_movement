
// Copyright by Vishnu Suresh


#include "PlayerStates/WallRun.h"

#include "MaterialHLSLTree.h"
#include "Character/Player/TF_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void UWallRun::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	
	Controller = CastChecked<AController>(PlayerCharacter->GetController());

	const FVector LaunchVelocity = FVector::CrossProduct(PlayerCharacter->GetWallNormal(),
		PlayerCharacter->GetActorUpVector()) * PlayerCharacter->GetWallRunSpeed() * PlayerCharacter->GetFacingDirection();

	PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
}

void UWallRun::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	if (PlayerCharacter->GetIsRunningOnWall() == false)
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
	if (!PlayerCharacter->GetCharacterMovement()->IsFalling())
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
	else if (PlayerCharacter->GetCharacterMovement()->IsFalling() && PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("WallJump");
	}
}

void UWallRun::ExitState()
{
	Super::ExitState();
	PlayerCharacter->SetIsRunningOnWall(false);
}


