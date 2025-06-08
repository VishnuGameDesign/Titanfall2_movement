// Copyright by Vishnu Suresh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RunnableWallInterface.h"
#include "RunnableWall.generated.h"

class ATF_Player;
class UBoxComponent;

UCLASS()
class TITANFALL2_MOVEMENT_API ARunnableWall : public AActor, public IRunnableWallInterface
{
	GENERATED_BODY()
	
public:	
	ARunnableWall();

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WallMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxComponent;
};
