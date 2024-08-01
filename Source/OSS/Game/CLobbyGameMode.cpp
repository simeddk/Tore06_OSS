#include "CLobbyGameMode.h"
#include "TimerManager.h"
#include "../OSS.h"
#include "CGameInstance.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++NumberOfPlayers;

	LogOnScreen(this, "Current Players : " + FString::FromInt(NumberOfPlayers));
	UE_LOG(LogTemp, Warning, TEXT("PostLogin : Current Players : %s"), *FString::FromInt(NumberOfPlayers));

	if (NumberOfPlayers >= 3)
	{
		LogOnScreen(this, "Reached 3 Players");
		UE_LOG(LogTemp, Error, TEXT("Reached 3 Players"));

		GetWorldTimerManager().SetTimer(GamerStartTimer, this, &ACLobbyGameMode::StartGame, 5.f);
	}
}

void ACLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	--NumberOfPlayers;

	UE_LOG(LogTemp, Warning, TEXT("Logout : Current Players : %s"), *FString::FromInt(NumberOfPlayers));
}

void ACLobbyGameMode::StartGame()
{
	UCGameInstance* GameInstance =  Cast<UCGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->StartSession();
	}

	UWorld* World = GetWorld();
	if (World)
	{
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/FPS?listen");
	}
}
