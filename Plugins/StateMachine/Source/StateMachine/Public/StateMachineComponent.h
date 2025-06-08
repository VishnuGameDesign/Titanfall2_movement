// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"
#include "StateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChangedSignature, const FGameplayTag&, NewStateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitStateSignature, const FGameplayTag&, StateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndStateSignature, const FGameplayTag&, StateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickStateSignature, float, DeltaTime, const FGameplayTag&, StateTag);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class STATEMACHINE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateMachineComponent();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString InitialState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bDebug = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, TSubclassOf<UStateBase>> AvailableStates;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, UStateBase*> StateMap;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UStateBase*> StateHistory;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 StateHistoryLength = 5;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStateBase> CurrentState = nullptr;

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void SwitchStateByKey(FString StateName);
	
	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void InitStateMachineComponent();

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	bool IsInState(FString State);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	FString GetCurrentStateName() { if (CurrentState != nullptr) return CurrentState->GetName(); else return ""; } ;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool bCanTickState = false;
	void InitializeStates();

};
