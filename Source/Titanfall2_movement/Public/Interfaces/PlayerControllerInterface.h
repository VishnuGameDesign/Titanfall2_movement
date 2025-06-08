// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllerInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_FourParams(FWalkSignature,APawn*, FVector, FVector, FVector2D)

UINTERFACE(MinimalAPI)
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

class TITANFALL2_MOVEMENT_API IPlayerControllerInterface
{
	GENERATED_BODY()

public:
	virtual FWalkSignature* GetWalkDelegate() = 0;
	virtual bool HasSprintRequested() = 0;
	virtual bool HasJumpRequested() = 0;
	virtual bool HasCrouchRequested() = 0;
 };
