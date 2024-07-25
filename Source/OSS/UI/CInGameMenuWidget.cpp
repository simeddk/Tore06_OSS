#include "CInGameMenuWidget.h"
#include "Components/Button.h"

bool UCInGameMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (bSuccess == false)
	{
		return false;
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UCInGameMenuWidget::CancelButtonPressed);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UCInGameMenuWidget::QuitButtonPressed);
	}

	return true;
}

void UCInGameMenuWidget::CancelButtonPressed()
{
	SetInputToGame();
}

void UCInGameMenuWidget::QuitButtonPressed()
{
	if (OwningInstance)
	{
		SetInputToUI();
		OwningInstance->OpenMainMenuLevel();
	}
}
