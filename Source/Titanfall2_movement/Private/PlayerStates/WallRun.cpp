
// Copyright by Vishnu Suresh


#include "PlayerStates/WallRun.h"
#include "Character/Player/TF_Player.h"
#include "Interfaces/PlayerControllerInterface.h"

void UWallRun::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->SetIsRunningOnWall(true);
	ElapsedTime = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("entered"));
}

void UWallRun::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	ElapsedTime += DeltaTime;
	if (PlayerCharacter->GetWallDetected() && ElapsedTime <= PlayerCharacter->GetWallRunDuration())
	{
		const FVector LaunchVelocity = FVector::CrossProduct(PlayerCharacter->GetWallNormal(),
			PlayerCharacter->GetActorUpVector()) * PlayerCharacter->GetWallRunSpeed() * PlayerCharacter->GetFacingDirection();

		PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}		
	else
	{
		RequestStateSwitch("OffTheWall");
	}

	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("WallJump");
	}
}

void UWallRun::ExitState()
{
	Super::ExitState();
	PlayerCharacter->SetIsRunningOnWall(false);
}


