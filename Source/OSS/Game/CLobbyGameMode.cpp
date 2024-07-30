#include "CLobbyGameMode.h"
#include "../OSS.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	++NumberOfPlayers;

	LogOnScreen(this, "Current Players : " + FString::FromInt(NumberOfPlayers));

	if (NumberOfPlayers >= 3)
	{
		LogOnScreen(this, "Reached 3 Players");
	}
}

void ACLobbyGameMode::Logout(APlayerController* Exiting)
{
	--NumberOfPlayers;
	//Todo. Build
}