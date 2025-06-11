// Copyright by Vishnu Suresh

#include "Character/Player/TF_Player.h"
#include "../../../../../Plugins/StateMachine/Source/StateMachine/Public/StateMachineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/PickupableInterface.h"

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

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphereComponent"));
	InteractionSphere->SetupAttachment(PlayerMesh);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	InteractionSphere->SetGenerateOverlapEvents(true);
}

void ATF_Player::BeginPlay()
{
	Super::BeginPlay();
	StateMachineComponent->InitStateMachineComponent();
}

void ATF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Wall Run Trace */
	if (GetCheckForWalls())
	{
		FHitResult RightHit, LeftHit;
		AActor* RightWall = CheckWall(GetActorRightVector(), RightHit);
		AActor* LeftWall = CheckWall(-GetActorRightVector(), LeftHit);
	
		if (RightWall)
		{
			bWallDetected = true;
			RunnableWall = RightWall;
			if (RunnableWall)
			{
				StartWallRunIfRightDirection(RightHit.Normal);
			}
		}
		else if (LeftWall)
		{
			bWallDetected = true;
			RunnableWall = LeftWall;
			if (RunnableWall)
			{
				StartWallRunIfRightDirection(LeftHit.Normal);
			}
		}
		else
		{
			bWallDetected = false;
		}
	}
	
	if (bIsRunningOnWall)
	{
		/* Camera Tilt when Wall Running */
		const float Roll = GetCameraTiltAngle() * GetFacingDirection();
		CameraTiltTo(Roll);

		/* Wall Run Duration Check */
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= WallRunDuration)
		{
			GetStateMachineComponent()->SwitchStateByKey("Walk");
			ElapsedTime = 0.0f;
			SetCheckForWalls(false);
			bCooldownStarted = true;
		}
	}
	else
	{
		CameraTiltTo(0.0f);

		/* Wall Run Cooldown */
		ElapsedTime = 0.0f;
		if (bCooldownStarted)
		{
			WallRunCooldown += DeltaTime;
			if (WallRunCooldown >= 1.0f)
			{
				SetCheckForWalls(true);
				WallRunCooldown = 0.0f;
				bCooldownStarted = false;
			}
		}
	}
}

void ATF_Player::InitInteraction()
{
	TArray<AActor*> OverlappingActors;
	InteractionSphere->GetOverlappingActors(OverlappingActors);
	
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			Interactable = TScriptInterface<IInteractableInterface>(OverlappingActor);
			if (Interactable)
			{
				Interactable->Interact();
			}
		}
		if (OverlappingActor->GetClass()->ImplementsInterface(UPickupableInterface::StaticClass()))
		{
			Pickupable = TScriptInterface<IPickupableInterface>(OverlappingActor);
			if (Pickupable)
			{
				Pickupable->Pickup(this);
			}
		}
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
		// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, HitResult.bBlockingHit ? FColor::Blue : FColor::Red, true, 1.f, 0, 1.f);
		if (HitResult.bBlockingHit && IsValid(HitResult.GetActor()))
		{
			return HitResult.GetActor();
		}
	}
	return nullptr;
}

void ATF_Player::StartWallRunIfRightDirection(const FVector& Normal)
{
	FacingDirection = FVector::DotProduct(GetActorRightVector(), Normal);
	if (FMath::Abs(FacingDirection) > 0.8f)
	{
		WallNormal = Normal;
		/* Switch to WallRunning State */
		if (GetCharacterMovement()->IsFalling() && bIsRunningOnWall == false)				
		{
			GetStateMachineComponent()->SwitchStateByKey("WallRun");
		}
	}
}

void ATF_Player::CameraTiltTo(const float Roll) const
{
	const FRotator CurrentRot = GetController()->GetControlRotation();
	const float Pitch = CurrentRot.Pitch; 
	const float Yaw = CurrentRot.Yaw;
	FRotator TargetRot = FRotator(Pitch, Yaw, Roll);
	FRotator NewRot = FMath::RInterpConstantTo(CurrentRot, TargetRot, GetWorld()->GetDeltaSeconds(), GetCameraTiltInterpSpeed());
	GetController()->SetControlRotation(NewRot);
}


