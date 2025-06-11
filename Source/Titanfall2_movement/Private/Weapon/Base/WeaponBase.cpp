// Copyright by Vishnu Suresh


#include "Weapon/Base/WeaponBase.h"
#include "Character/Player/TF_Player.h"
#include "Components/SphereComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionObjectType(ECC_PhysicsBody);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	WeaponMesh->SetCastShadow(false);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(WeaponMesh);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldStatic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

void AWeaponBase::Pickup(AActor* OwnerActor)
{
	if (OwnerActor)
	{
		PlayerRef = Cast<ATF_Player>(OwnerActor);
		if (PlayerRef)
		{
			AttachToComponent(PlayerRef->GetPlayerSkeletalMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PlayerRef->GetWeaponSocketName());
			SetActorEnableCollision(false);
			PlayerRef->SetIsCarryingWeapon(true);
		}
	}
}

void AWeaponBase::Drop()
{
	PlayerRef->SetIsCarryingWeapon(false);
}
