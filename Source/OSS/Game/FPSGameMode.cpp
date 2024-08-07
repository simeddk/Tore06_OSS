#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Characters/FPSCharacter.h"
#include "../OSS.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_CPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
	PlayerStateClass = ACPlayerState::StaticClass();
}

void AFPSGameMode::StartPlay()
{
	Super::StartPlay();

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		if (It->PlayerStartTag == "Red")
		{
			if (RedTeamPlayerStarts.Find(*It) < 0)
			{
				RedTeamPlayerStarts.Add(*It);
			}
		}
		else
		{
			if (BlueTeamPlayerStarts.Find(*It) < 0)
			{
				BlueTeamPlayerStarts.Add(*It);
			}
		}
	}

	LogOnScreen(this, "RedTeam : " + FString::FromInt(RedTeamPlayerStarts.Num()), FColor::Red);
	LogOnScreen(this, "BlueTeam : " + FString::FromInt(BlueTeamPlayerStarts.Num()), FColor::Blue);
}

void AFPSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AFPSCharacter* PlayerCharacter = NewPlayer->GetPawn<AFPSCharacter>();
	ACPlayerState* PS = NewPlayer->GetPlayerState<ACPlayerState>();
	if (PlayerCharacter && PS)
	{
		if (RedTeamPawns.Num() > BlueTeamPawns.Num())
		{
			PS->Team = ETeamType::Blue;
			BlueTeamPawns.Add(PlayerCharacter);
		}
		else
		{
			PS->Team = ETeamType::Red;
			RedTeamPawns.Add(PlayerCharacter);
		}
	}

	PlayerCharacter->SetTeamColor(PS->Team);
	MoveToPlayerStart(PlayerCharacter, PS->Team);
}

void AFPSGameMode::MoveToPlayerStart(APawn* Pawn, ETeamType Team)
{
	if (RedTeamPlayerStarts.Num() < 1 || BlueTeamPlayerStarts.Num() < 1)
	{
		StartPlay();
	}

	int32 Random = 0;
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;

	switch (Team)
	{
		case ETeamType::Red:
		{
			Random = UKismetMathLibrary::RandomInteger(RedTeamPlayerStarts.Num() - 1);
			Location = RedTeamPlayerStarts[Random]->GetActorLocation();
			Rotation = RedTeamPlayerStarts[Random]->GetActorRotation();
		}
		break;

		case ETeamType::Blue:
		{
			Random = UKismetMathLibrary::RandomInteger(BlueTeamPlayerStarts.Num() - 1);
			Location = BlueTeamPlayerStarts[Random]->GetActorLocation();
			Rotation = BlueTeamPlayerStarts[Random]->GetActorRotation();
		}
		break;
	}

	Pawn->SetActorLocation(Location);
	
	if (Pawn->GetController())
	{
		Pawn->GetController()->ClientSetRotation(Rotation, true);
	}
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

		AFPSCharacter* NewPlayerCharacter = Controller->GetPawn<AFPSCharacter>();
		ACPlayerState* PS = Controller->GetPlayerState<ACPlayerState>();
		if (PS)
		{
			NewPlayerCharacter->SetTeamColor(PS->Team);
			MoveToPlayerStart(NewPlayerCharacter, PS->Team);
		}
	}
}