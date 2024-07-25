#include "CMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

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
	ensure(OwningInstance);
	ensure(IPAddressField);

	const FString& IP = IPAddressField->GetText().ToString();
	OwningInstance->Join(IP);
}

void UCMainMenuWidget::SwitchJoinMenu()
{
	ensure(MenuSwitcher);
	ensure(JoinMenu);
	
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
