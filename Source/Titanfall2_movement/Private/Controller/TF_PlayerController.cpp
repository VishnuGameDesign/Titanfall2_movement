// Copyright by Vishnu Suresh


#include "Controller/TF_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/Player/TF_Player.h"


ATF_PlayerController::ATF_PlayerController()
{
	bReplicates = true;
}

void ATF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerIMC);
	check(WeaponIMC);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerIMC, 0);
		Subsystem->AddMappingContext(WeaponIMC, 0);
	}
}

void ATF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	// input action bindings
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATF_PlayerController::Move);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATF_PlayerController::Look);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &ATF_PlayerController::StartSprint);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATF_PlayerController::StopSprint);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ATF_PlayerController::StartJump);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATF_PlayerController::StopJump);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATF_PlayerController::StartCrouch);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ATF_PlayerController:: StopCrouch);
}

void ATF_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacter = CastChecked<ATF_Player>(InPawn);
}

void ATF_PlayerController::Look(const FInputActionValue& InputValue)
{
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();

	FRotator Rotation = GetControlRotation();

	Rotation.Yaw += InputAxisVector.X;
	Rotation.Pitch += InputAxisVector.Y;

	Rotation.Pitch = FMath::ClampAngle(Rotation.Pitch, -ClampAngle, ClampAngle) + InputAxisVector.Y;
	SetControlRotation(Rotation);
}

void ATF_PlayerController::StartSprint(const FInputActionValue& InputValue)
{
	bSprintRequested = true;
}

void ATF_PlayerController::StopSprint(const FInputActionValue& InputValue)
{
	bSprintRequested = false;
}

void ATF_PlayerController::StartJump(const FInputActionValue& InputValue)
{
	bJumpRequested = true;
}

void ATF_PlayerController::StopJump(const FInputActionValue& InputValue)
{
	bJumpRequested = false;
}

void ATF_PlayerController::StartCrouch(const FInputActionValue& InputValue)
{
	bCrouchPressed = !bCrouchPressed;
	bCrouchRequested = true;
	PlayerCharacter->SetBeginCrouching(true);
}

void ATF_PlayerController::StopCrouch(const FInputActionValue& InputValue)
{
	bCrouchRequested = false;
	if (!bCrouchPressed)
		PlayerCharacter->SetBeginCrouching(false);
}

void ATF_PlayerController::Move(const FInputActionValue& InputValue)
{
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = Cast<APawn>(GetPawn()))
	{
		if (WalkDelegate.IsBound())
			WalkDelegate.Broadcast(ControlledPawn, ForwardDirection, RightDirection, InputAxisVector);
	}
}

