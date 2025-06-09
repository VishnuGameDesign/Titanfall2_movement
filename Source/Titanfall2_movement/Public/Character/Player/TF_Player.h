// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "StateMachineComponent.h"
#include "Character/TF_CharacterBase.h"
#include "Interfaces/RunnableWallInterface.h"
#include "TF_Player.generated.h"

#define ECC_WALL_RUN ECC_GameTraceChannel1

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TITANFALL2_MOVEMENT_API ATF_Player : public ATF_CharacterBase
{
	GENERATED_BODY()

public:
	ATF_Player();
	UFUNCTION()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/* Helper Functions */
	UFUNCTION(BlueprintCallable)
	UStateMachineComponent* GetStateMachineComponent() { return StateMachineComponent; };

	UFUNCTION(BlueprintCallable)
	float GetSprintSpeed() const { return SprintSpeed; };

	UFUNCTION(BlueprintCallable)
	float GetWalkSpeed() const { return WalkSpeed; }

	UFUNCTION(BlueprintCallable)
	float GetCrouchSpeed() const { return CrouchSpeed; }

	UFUNCTION(BlueprintCallable)
	float GetCrouchedCapsuleHalfHeight() const { return CrouchedCapsuleHalfHeight; }

	UFUNCTION(BlueprintCallable)
	float GetStandingCapsuleHalfHeight() const { return StandingCapsuleHalfHeight; }

	UFUNCTION(BlueprintCallable)
	float GetCrouchInterpSpeed() const { return CrouchInterpSpeed; }

	UFUNCTION(BlueprintCallable)
	bool GetCrouchingState() const { return StartCrouching; }
	
	UFUNCTION(BlueprintCallable)
	void SetBeginCrouching(const bool bValue) { StartCrouching = bValue; }

	UFUNCTION(BlueprintCallable)
	float GetDoubleJumpVelocity() const { return DoubleJumpZVelocity; }

	UFUNCTION(BlueprintCallable)
	float GetSlideSpeed() const { return SlideSpeed; }

	UFUNCTION(BlueprintCallable)
	float GetDefaultGroundFriction() const { return DefaultGroundFriction; }

	UFUNCTION(BlueprintCallable)
	float GetSlideGroundFriction() const { return SlideGroundFriction; }
	
	UFUNCTION(BlueprintCallable)
	float GetSlideDuration() const { return SlideDuration; }
	
	UFUNCTION(BlueprintCallable)
	bool GetIsRunningOnWall() const { return bIsRunningOnWall; }

	UFUNCTION(BlueprintCallable)
	void SetIsRunningOnWall(bool bValue) { bIsRunningOnWall = bValue; }

	UFUNCTION(BlueprintCallable)
	float GetWallRunSpeed() const { return WallRunSpeed; }
	
	UFUNCTION(BlueprintCallable)
	FVector GetWallNormal() const { return WallNormal; }

	UFUNCTION(BlueprintCallable)
	float GetWallRunDuration() const { return WallRunDuration; }

	UFUNCTION(BlueprintCallable)
	float GetWallRunCooldown() const { return WallRunCooldown; }

	UFUNCTION(BlueprintCallable)
	float GetFacingDirection() const { return FacingDirection; }

	UFUNCTION(BlueprintCallable)
	float GetJumpXForce() const { return JumpXForce; }

	UFUNCTION(BlueprintCallable)
	float GetJumpZForce() const { return JumpZForce; }
	
	UFUNCTION(BlueprintCallable)
	float GetJumpYForce() const { return JumpYForce; }

	UFUNCTION(BlueprintCallable)
	int32 GetDefaultJumpMaxCount() const { return DefaultJumpMaxCount; }

	UFUNCTION(BlueprintCallable)
	int32 GetWallJumpMaxCount() const { return WallJumpMaxCount; }

	UFUNCTION(BlueprintCallable)
	float GetCameraTiltAngle() const { return CameraTiltAngle; }

	UFUNCTION(BlueprintCallable)
	float GetCameraTiltInterpSpeed() const { return CameraTiltInterpSpeed; }

	UFUNCTION(BlueprintCallable)
	bool GetWallDetected() const { return bWallDetected; }

	UFUNCTION(BlueprintCallable)
	bool GetCheckForWalls() const { return bInitCheckForWalls; }

	UFUNCTION(BlueprintCallable)
	void SetCheckForWalls(const bool bValue) { bInitCheckForWalls = bValue; } 

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> PlayerCam;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TObjectPtr<USkeletalMeshComponent> PlayerMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	float SprintSpeed = 800.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Walk")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crouch")
	float CrouchSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crouch")
	float CrouchedCapsuleHalfHeight = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crouch")
	float StandingCapsuleHalfHeight = 88.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crouch")
	float CrouchInterpSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crouch")
	bool StartCrouching = false;

	UPROPERTY(EditDefaultsOnly, Category = "Jump")
	float DoubleJumpZVelocity = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float SlideSpeed = 1200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float DefaultGroundFriction = 8.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float SlideGroundFriction = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Slide")
	float SlideDuration = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	float LineTraceDistance = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	float WallRunSpeed = 1200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	float FacingDirection = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	FVector WallNormal = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	float WallRunDuration = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run")
	float WallRunCooldown = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Jump")
	float JumpXForce = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Jump")
	float JumpZForce = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Jump")
	float JumpYForce = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Jump")
	int32 WallJumpMaxCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Jump")
	int32 DefaultJumpMaxCount = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run Camera Settings")
	float CameraTiltAngle = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "Wall Run Camera Settings")
	float CameraTiltInterpSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "StateMachine")
	TObjectPtr<UStateMachineComponent> StateMachineComponent;
	
private:
	bool bIsRunningOnWall = false;
	bool bWallDetected = false;
	bool bInitCheckForWalls = true;
	TScriptInterface<IRunnableWallInterface> RunnableWall;
	AActor* CheckWall(const FVector& Direction, FHitResult& HitResult);
	void StartWallRunIfRightDirection(const FVector& Normal);
	void CameraTiltTo(float Roll) const;
};
