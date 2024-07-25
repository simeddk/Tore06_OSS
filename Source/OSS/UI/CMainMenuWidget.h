#pragma once

#include "CoreMinimal.h"
#include "CMenuWidgetBase.h"
#include "CMainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UEditableTextBox;

UCLASS()
class OSS_API UCMainMenuWidget : public UCMenuWidgetBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void SwitchJoinMenu();
	
	UFUNCTION()
	void SwitchMainMenu();

	UFUNCTION()
	void QuitPressed();
	
protected:
	//Buttons
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	//Widgets
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAddressField;


};
