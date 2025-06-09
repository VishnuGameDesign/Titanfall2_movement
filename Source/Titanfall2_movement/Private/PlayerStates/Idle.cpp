// Copyright by Vishnu Suresh


#include "PlayerStates/Idle.h"
#include "Interfaces/PlayerControllerInterface.h"

void UIdle::EnterState(AActor* Owner)
{
	Super::EnterState(Owner);
}

void UIdle::TickState(float DelaTime)
{
	Super::TickState(DelaTime);
	if (IsPlayerMoving())
	{
		RequestStateSwitch("Walk");
	}
	if (PlayerControllerInterface->HasJumpRequested())
	{
		RequestStateSwitch("Jump");
	}
	if (PlayerControllerInterface->HasCrouchRequested())
	{
		RequestStateSwitch("Crouch");
	}
}
