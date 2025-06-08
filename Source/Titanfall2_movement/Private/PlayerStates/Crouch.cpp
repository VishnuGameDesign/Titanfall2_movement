// Copyright by Vishnu Suresh

#include "PlayerStates/Crouch.h"
#include "Character/Player/TF_Player.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCrouch::HandleWalk(APawn* ControlledPawn, FVector Fwd, FVector Right, FVector2D InputAxis)
{
	Super::HandleWalk(ControlledPawn, Fwd, Right, InputAxis);
}

void UCrouch::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetCrouchSpeed();
}

void UCrouch::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	if (PlayerCharacter->GetCrouchingState())
	{
		CrouchToTargetHeight(PlayerCharacter->GetCrouchedCapsuleHalfHeight(), DeltaTime);
	}
	else
	{
		CrouchToTargetHeight(PlayerCharacter->GetStandingCapsuleHalfHeight(), DeltaTime);
		if (FMath::IsNearlyEqual(PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), PlayerCharacter->GetStandingCapsuleHalfHeight(), 1.5f))
		{
			IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
		}
	}
}

void UCrouch::ExitState()
{
	Super::ExitState();
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetWalkSpeed();
}

