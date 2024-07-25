#pragma once

#include "CoreMinimal.h"
#include "CMenuWidgetBase.h"
#include "CInGameMenuWidget.generated.h"

class UButton;

UCLASS()
class OSS_API UCInGameMenuWidget : public UCMenuWidgetBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void CancelButtonPressed();

	UFUNCTION()
	void QuitButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
};
