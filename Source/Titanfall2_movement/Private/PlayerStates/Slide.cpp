// Copyright by Vishnu Suresh


#include "PlayerStates/Slide.h"

#include "Character/Player/TF_Player.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"

void USlide::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetSlideSpeed();
	PlayerCharacter->GetCharacterMovement()->GroundFriction = PlayerCharacter->GetSlideGroundFriction();
}

void USlide::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	ElapsedTime += DeltaTime;
	if (ElapsedTime < PlayerCharacter->GetSlideDuration() && PlayerCharacter->GetCrouchingState())
	{
		CrouchToTargetHeight(PlayerCharacter->GetCrouchedCapsuleHalfHeight(), DeltaTime);
	}
	else if (ElapsedTime >= PlayerCharacter->GetSlideDuration())
	{
		StopSliding(DeltaTime);
	}
	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("Jump");
	}
}

void USlide::ExitState()
{
	Super::ExitState();
	IsPlayerSprinting() ? PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetSprintSpeed() : PlayerCharacter->GetWalkSpeed();
	PlayerCharacter->GetCharacterMovement()->GroundFriction = PlayerCharacter->GetDefaultGroundFriction();
	ElapsedTime = 0.0f;
}

void USlide::StopSliding(float DeltaTime)
{
	CrouchToTargetHeight(PlayerCharacter->GetStandingCapsuleHalfHeight(), DeltaTime);
	if (FMath::IsNearlyEqual(PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), PlayerCharacter->GetStandingCapsuleHalfHeight(), 1.5f))
	{
		IsPlayerMoving() ? RequestStateSwitch("Walk") : RequestStateSwitch("Idle");
	}
}
