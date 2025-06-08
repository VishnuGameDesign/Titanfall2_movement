// Copyright by Vishnu Suresh

#include "StateMachine/Public/StateMachineComponent.h"

UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeStates();
}

void UStateMachineComponent::InitializeStates()
{
	for (auto It  = AvailableStates.CreateConstIterator(); It; ++It)
	{
		UStateBase* State = NewObject<UStateBase>(this, It.Value());
		StateMap.Add(It.Key(), State);
	}
}

void UStateMachineComponent::SwitchStateByKey(FString StateName)
{
	UStateBase* NewState = StateMap.FindRef(StateName);
	if (NewState->IsValidLowLevel())
	{
		if (!CurrentState)
		{
			CurrentState = NewState;
		}
		else
		{
			if (CurrentState->GetClass() == NewState->GetClass() && CurrentState->bCanRepeatState == false)
			{
				if (bDebug)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
						FString::Printf(TEXT("%s's state switch failed. %s is not repeatable"),
							*GetOwner()->GetName(), *CurrentState->StateDisplayName.GetPlainNameString()));

				}
			}
			else
			{
				bCanTickState = false;
				CurrentState->ExitState();
				if (StateHistory.Num() < StateHistoryLength)
					StateHistory.Push(CurrentState);
				else
				{
					StateHistory.RemoveAt(0);
					StateHistory.Push(CurrentState);
				}
				CurrentState = NewState;
			}
		}
		if (CurrentState)
		{
			CurrentState->EnterState(GetOwner());
			bCanTickState = true;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Invalid State!"));
	}
}

void UStateMachineComponent::InitStateMachineComponent()
{
	SwitchStateByKey(InitialState);
}

bool UStateMachineComponent::IsInState(FString State)
{
	if (!CurrentState->IsValidLowLevel())
		return false;

	if (UStateBase* StateToCheck = StateMap.FindRef(State))
	{
		return StateToCheck->GetClass() == CurrentState->GetClass();
	}

	return false;
}

void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanTickState)
		CurrentState->TickState(DeltaTime);

	if (bDebug)
	{
		if (CurrentState)
			UE_LOG(LogTemp, Display, TEXT("%s"), *CurrentState->StateDisplayName.GetPlainNameString());
		if (StateHistory.Num() < StateHistoryLength)
		{
			for (int32 i = 0; i < StateHistory.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%s"), *StateHistory[i]->GetName()));
			}
		}
	}
}

void UStateMachineComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	StateHistory.Empty();
	CurrentState = nullptr;
}


