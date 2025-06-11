// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPickupableInterface : public UInterface
{
	GENERATED_BODY()
};

class TITANFALL2_MOVEMENT_API IPickupableInterface
{
	GENERATED_BODY()

public:
	virtual void Pickup(AActor* Owner) = 0;
	virtual void Drop() = 0;
};
