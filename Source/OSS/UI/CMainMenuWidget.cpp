#include "CMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "CSessionRowWidget.h"

UCMainMenuWidget::UCMainMenuWidget()
{
	ConstructorHelpers::FClassFinder<UUserWidget> SessionRowClassAsset(TEXT("/Game/UI/WB_SessionRow"));
	
	if (SessionRowClassAsset.Succeeded())
	{
		SessionRowClass = SessionRowClassAsset.Class;
	}
}

bool UCMainMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (bSuccess == false)
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UCMainMenuWidget::HostServer);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UCMainMenuWidget::SwitchJoinMenu);
	}

	if (CancelJoinMenuButton)
	{
		CancelJoinMenuButton->OnClicked.AddDynamic(this, &UCMainMenuWidget::SwitchMainMenu);
	}

	if (JoinServerButton)
	{
		JoinServerButton->OnClicked.AddDynamic(this, &UCMainMenuWidget::JoinServer);
	}

	if (QuitButton)
	{	
		QuitButton->OnClicked.AddDynamic(this, &UCMainMenuWidget::QuitPressed);
	}

	return true;
}

void UCMainMenuWidget::HostServer()
{
	ensure(OwningInstance);

	OwningInstance->Host();
}

void UCMainMenuWidget::JoinServer()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectedIndex : %d"), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectedIndex is not set yet"));
	}

	//ensure(OwningInstance);
	//OwningInstance->Join("");
}

void UCMainMenuWidget::SwitchJoinMenu()
{
	ensure(MenuSwitcher);
	ensure(JoinMenu);
	ensure(OwningInstance);

	OwningInstance->StartFindSession();

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UCMainMenuWidget::SwitchMainMenu()
{
	ensure(MenuSwitcher);
	ensure(MainMenu);

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenuWidget::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		PC->ConsoleCommand("Quit");
	}
}

void UCMainMenuWidget::SetSessionList(TArray<FString> InSessionNames)
{
	SessionList->ClearChildren();

	uint32 i = 0;
	for (const auto& SessionName : InSessionNames)
	{
		UCSessionRowWidget* SessionRow = CreateWidget<UCSessionRowWidget>(this, SessionRowClass);

		if (SessionRow)
		{
			SessionRow->SessionName->SetText(FText::FromString(SessionName));
			SessionRow->Setup(this, i++);
			SessionList->AddChild(SessionRow);
		}
	}
}

void UCMainMenuWidget::SetSelectedIndex(uint32 InIndex)
{
	SelectedIndex = InIndex;
}
//Todo. build
