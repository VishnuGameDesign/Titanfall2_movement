// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class TITANFALL2_MOVEMENT_API IInteractableInterface
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
};
