#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "../OSS.h"
#include "../UI/CMainMenuWidget.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassAsset(TEXT("/Game/UI/WB_MainMenu"));

	if (WidgetClassAsset.Succeeded())
	{
		MainMenuWidgetClass = WidgetClassAsset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	
}

void UCGameInstance::Host()
{
	LogOnScreen(this, "Host", FColor::Green);
	
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

void UCGameInstance::LoadMainMenu()
{
	MainMenu = CreateWidget<UCMainMenuWidget>(this, MainMenuWidgetClass);
	if (!MainMenu)
	{
		return;
	}

	MainMenu->SetOwningInstance(this);
	MainMenu->SetInputToUI();
}