// Copyright by Vishnu Suresh

#include "Character/Player/TF_Player.h"
#include "../../../../../Plugins/StateMachine/Source/StateMachine/Public/StateMachineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/RunnableWallInterface.h"
#include "DrawDebugHelpers.h"
#include "PlayerStates/WallRun.h"

ATF_Player::ATF_Player()
{
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(RootComponent);
	PlayerCam->bUsePawnControlRotation = true;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(PlayerCam);
	PlayerMesh->SetOnlyOwnerSee(true);
	PlayerMesh->bCastDynamicShadow = false;
	PlayerMesh->CastShadow = false;

	StateMachineComponent = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachineComponent"));

	GetMesh()->SetOwnerNoSee(true);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ATF_Player::BeginPlay()
{
	Super::BeginPlay();
	StateMachineComponent->InitStateMachineComponent();

	// TODO: WallRunDuration
}

void ATF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/* Wall Run Trace */
	FHitResult RightHit, LeftHit;
		
	AActor* RightWall = CheckWall(GetActorRightVector(), RightHit);
	AActor* LeftWall = CheckWall(-GetActorRightVector(), LeftHit);
	
	if (RightWall)
	{
		RunnableWall = RightWall;
		if (RunnableWall)
		{
			CheckFacingWallDirection(RightHit.Normal);
		}
	}
	else if (LeftWall)
	{
		RunnableWall = LeftWall;
		if (RunnableWall)
		{
			CheckFacingWallDirection(LeftHit.Normal);
		}
	}

	/* Camera Tilt when Wall Running */
	if (IsRunningOnWall)
	{
		float Roll = GetCameraTiltAngle() * GetFacingDirection();
		CameraTiltTo(Roll);
	}
	else
	{
		CameraTiltTo(0.0f);
	}
}

AActor* ATF_Player::CheckWall(const FVector& Direction, FHitResult& HitResult)
{
	const FVector TraceStart = GetActorLocation();
	const FVector TraceEnd = TraceStart + Direction * LineTraceDistance;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WALL_RUN, Params))
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, HitResult.bBlockingHit ? FColor::Blue : FColor::Red, true, 1.f, 0, 1.f);
		if (HitResult.bBlockingHit && IsValid(HitResult.GetActor()))
		{
			return HitResult.GetActor();
		}
	}
	return nullptr;
}

void ATF_Player::CheckFacingWallDirection(const FVector& Normal)
{
	FacingDirection = FVector::DotProduct(GetActorRightVector(), Normal);
	if (FMath::Abs(FacingDirection) > 0.8f)
	{
		WallNormal = Normal;
		/* Switch to WallRunning State */
		if (GetCharacterMovement()->IsFalling())
		{
			GetStateMachineComponent()->SwitchStateByKey("WallRun");
			SetIsRunningOnWall(true);
		}
	}
}

void ATF_Player::CameraTiltTo(float Roll)
{
	FRotator CurrentRot = GetController()->GetControlRotation();
	const float Pitch = CurrentRot.Pitch; 
	const float Yaw = CurrentRot.Yaw;
	FRotator TargetRot = FRotator(Pitch, Yaw, Roll);
	FRotator NewRot = FMath::RInterpConstantTo(CurrentRot, TargetRot, GetWorld()->GetDeltaSeconds(), GetCameraTiltInterpSpeed());
	GetController()->SetControlRotation(NewRot);
}



