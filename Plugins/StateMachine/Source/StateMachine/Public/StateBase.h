// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "StateBase.generated.h"

UCLASS(Abstract)
class STATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanTickState = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bCanRepeatState = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName StateDisplayName;

	public:
	virtual void EnterState(AActor* Owner) {};
	virtual void TickState(float DeltaTime) {};
	virtual void ExitState() {};
};
