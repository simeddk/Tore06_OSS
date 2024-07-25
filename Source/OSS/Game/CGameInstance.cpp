#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"

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
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, TEXT("MySession"), SessionSettings);
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

//Todo. Host Button Pressed Crashed
void UCGameInstance::OnCreateSessionCompleted(FName InSessionName, bool bWasSuccessful)
{
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
