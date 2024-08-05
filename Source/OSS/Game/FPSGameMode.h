#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS(minimalapi)
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameMode();

public:
	void OnActorKilled(AActor* VictimActor);

private:
	UFUNCTION()
	void RespawnPlayerElpased(APlayerController* Controller);
};



