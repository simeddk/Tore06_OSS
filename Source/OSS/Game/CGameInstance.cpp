#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"

const static FName SESSION_NAME = TEXT("GameSession");

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClassAsset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuWidgetClassAsset.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameWidgetClassAsset(TEXT("/Game/UI/WB_InGameMenu"));
	if (InGameWidgetClassAsset.Succeeded())
	{
		InGameMenuWidgetClass = InGameWidgetClassAsset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		UE_LOG(LogTemp, Display, TEXT("OSS Name : %s"), *OSS->GetSubsystemName().ToString());

		SessionInterface = OSS->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Display, TEXT("Session Interface found"));

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionCompleted);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionCompleted);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCGameInstance::OnFindSessionCompleted);
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Not found OSS"));
	}
}

void UCGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExsistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExsistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession_Internal();
		}
	}
}

void UCGameInstance::CreateSession_Internal()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UCGameInstance::Join(const FString& InAddress)
{
	LogOnScreen(this, "Join to " + InAddress, FColor::Green);
	
	if (MainMenu)
	{
		MainMenu->SetInputToGame();
	}

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::OpenMainMenuLevel()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		return;
	}

	PC->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::StartFindSession()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		LogOnScreen(this, "Start Finding Session");

		SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UCGameInstance::LoadMainMenu()
{
	ensure(MainMenuWidgetClass);

	MainMenu = CreateWidget<UCMainMenuWidget>(this, MainMenuWidgetClass);
	if (!MainMenu)
	{
		return;
	}

	MainMenu->SetOwningInstance(this);
	MainMenu->SetInputToUI();
}

void UCGameInstance::LoadInGameMenu()
{
	ensure(InGameMenuWidgetClass);

	UCMenuWidgetBase* InGameMenu = CreateWidget<UCMenuWidgetBase>(this, InGameMenuWidgetClass);
	if (!InGameMenu)
	{
		return;
	}

	InGameMenu->SetOwningInstance(this);
	InGameMenu->SetInputToUI();
}

void UCGameInstance::OnCreateSessionCompleted(FName InSessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Error, TEXT("Created Session")); //Hack

	if (!bWasSuccessful)
	{
		LogOnScreen(this, "Could not create session!", FColor::Red);
		return;
	}

	LogOnScreen(this, "Create Session Completed, Session Name : " + InSessionName.ToString(), FColor::Green);

	if (MainMenu)
	{
		MainMenu->SetInputToGame();
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::OnDestroySessionCompleted(FName InSessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Error, TEXT("Destroied Session")); //Hack

	if (bWasSuccessful)
	{
		CreateSession_Internal();
	}
}

void UCGameInstance::OnFindSessionCompleted(bool bWasSuccessful)
{
	if (bWasSuccessful && SessionSearch.IsValid() && MainMenu)
	{
		LogOnScreen(this, "Finish Finding Session");

		TArray<FString> SessionList;

		for (const auto& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Error, TEXT("Found Session ID : %s"), *SearchResult.GetSessionIdStr());
			UE_LOG(LogTemp, Error, TEXT("Ping(ms) : %d"), SearchResult.PingInMs);

			SessionList.Add(SearchResult.GetSessionIdStr());
		}

		MainMenu->SetSessionList(SessionList);
	}

}
