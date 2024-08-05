#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "../Characters/FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "CPlayerState.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_CPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
	PlayerStateClass = ACPlayerState::StaticClass();
}

void AFPSGameMode::OnActorKilled(AActor* VictimActor)
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElpased", Player->GetController());

		float RespawnDelay = 3.f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}
}

void AFPSGameMode::RespawnPlayerElpased(APlayerController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);

		ACPlayerState* PS = Controller->GetPlayerState<ACPlayerState>();
		if (PS)
		{
			//Todo. 죽은 후 리스폰 되는지
		}
	}
}
