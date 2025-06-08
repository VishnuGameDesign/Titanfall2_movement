// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PlayerControllerInterface.h"
#include "TF_PlayerController.generated.h"

class ATF_Player;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TITANFALL2_MOVEMENT_API ATF_PlayerController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()
	
public:
	ATF_PlayerController();

	FWalkSignature WalkDelegate;

	virtual bool HasSprintRequested() override { return bSprintRequested; }
	virtual bool HasJumpRequested() override { return bJumpRequested; }
	virtual bool HasCrouchRequested() override { return bCrouchRequested; }
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	FORCEINLINE virtual FWalkSignature* GetWalkDelegate() override { return &WalkDelegate; };
	

private:
	// Input Mapping Contexts 
	UPROPERTY(EditDefaultsOnly, Category = "Input Maps")
	TObjectPtr<UInputMappingContext> PlayerIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input Maps")
	TObjectPtr<UInputMappingContext> WeaponIMC;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> PickupAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> DropAction;

	UPROPERTY(EditDefaultsOnly, Category = "Control Rotation")
	float ClampAngle = 50.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TObjectPtr<ATF_Player> PlayerCharacter;
	
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void StartSprint(const FInputActionValue& InputValue);
	void StopSprint(const FInputActionValue& InputValue);
	void StartJump(const FInputActionValue& InputValue);
	void StopJump(const FInputActionValue& InputValue);
	void StartCrouch(const FInputActionValue& InputValue);
	void StopCrouch(const FInputActionValue& InputValue);

	bool bCrouchPressed = false;
	bool bSprintRequested = false;
	bool bJumpRequested = false;
	bool bCrouchRequested = false;
};
