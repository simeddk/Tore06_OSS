#pragma once

#include "CoreMinimal.h"
#include "../OSSGameMode.h"
#include "CLobbyGameMode.generated.h"

UCLASS()
class OSS_API ACLobbyGameMode : public AOSSGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
private:
	void StartGame();

private:
	uint32 NumberOfPlayers;
	FTimerHandle GamerStartTimer;
};
