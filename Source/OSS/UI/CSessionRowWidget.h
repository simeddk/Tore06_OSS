#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSessionRowWidget.generated.h"

class UTextBlock;
class UCMainMenuWidget;
class UButton;

UCLASS()
class OSS_API UCSessionRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(UCMainMenuWidget* InParentWidget, uint32 InSelfIndex);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionName;

private:
	UFUNCTION()
	void OnClicked();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* RowButton;

private:
	UCMainMenuWidget* ParentWidget;
	uint32 SelfIndex;
};
