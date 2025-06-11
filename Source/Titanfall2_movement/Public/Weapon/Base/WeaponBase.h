// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/PickupableInterface.h"
#include "WeaponBase.generated.h"

class ATF_Player;
class USphereComponent;
class USkeletalMeshComponent;

UCLASS(Abstract)
class TITANFALL2_MOVEMENT_API AWeaponBase : public AActor, public IPickupableInterface
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();
	
protected:
	virtual void Pickup(AActor* OwnerActor) override;
	virtual void Drop() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<ATF_Player> PlayerRef;
	 
};
