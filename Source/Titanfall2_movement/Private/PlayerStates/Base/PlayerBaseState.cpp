// Copyright by Vishnu Suresh


#include "PlayerStates/Base/PlayerBaseState.h"
#include "Character/Player/TF_Player.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "Kismet/GameplayStatics.h"

void UPlayerBaseState::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);

	if (!PlayerCharacter)
		PlayerCharacter = Cast<ATF_Player>(Owner);

	if (!PlayerControllerInterface)
		PlayerControllerInterface = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerControllerInterface)
	{
		PlayerControllerInterface->GetWalkDelegate()->AddUObject(this, &UPlayerBaseState::HandleWalk);
		//TODO: Slide, WallRunning, WallJumping
	}
}

void UPlayerBaseState::ExitState()
{
	Super::ExitState();
	PlayerControllerInterface->GetWalkDelegate()->RemoveAll(this);
}

void UPlayerBaseState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
}

void UPlayerBaseState::HandleWalk(APawn* ControlledPawn, const FVector Fwd, const FVector Right, const FVector2D InputAxis)
{
	ControlledPawn->AddMovementInput(Fwd, InputAxis.Y);
	ControlledPawn->AddMovementInput(Right, InputAxis.X);
}

bool UPlayerBaseState::IsPlayerMoving()
{
	if (PlayerCharacter->GetCharacterMovement()->GetLastUpdateVelocity().Length() > 0)
		return true;

	return false;
}

bool UPlayerBaseState::IsPlayerSprinting()
{
	if (PlayerCharacter->GetCharacterMovement()->GetLastUpdateVelocity().SizeSquared() > FMath::Square(PlayerCharacter->GetSprintSpeed()))
	{
		return true;
	}

	return false;
}

void UPlayerBaseState::RequestStateSwitch(const FString& StateName)
{
	PlayerCharacter->GetStateMachineComponent()->SwitchStateByKey(StateName);
}

void UPlayerBaseState::CrouchToTargetHeight(float TargetHeight, float Time)
{
	float CurrentCapsuleHalfHeight = PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float NewHeight = FMath::FInterpTo(CurrentCapsuleHalfHeight, TargetHeight, Time, PlayerCharacter->GetCrouchInterpSpeed());

	float Difference = FMath::Abs(NewHeight - TargetHeight);
	if (Difference < 0.1f)
	{
		NewHeight = TargetHeight;
	}
	else
	{
		// UE_LOG(LogTemp, Error, TEXT("Target Height not achieved! Difference: %f"), Difference);
	}

	PlayerCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(NewHeight, true);
}



