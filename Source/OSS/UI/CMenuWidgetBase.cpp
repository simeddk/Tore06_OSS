#include "CMenuWidgetBase.h"

void UCMenuWidgetBase::SetOwningInstance(ICMenuInterface* InOwningInstance)
{
	OwningInstance = InOwningInstance;
}

void UCMenuWidgetBase::SetInputToUI()
{
	AddToViewport();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void UCMenuWidgetBase::SetInputToGame()
{
	RemoveFromParent();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}
