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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HostUser;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConnectionFraction;

private:
	UFUNCTION()
	void OnClicked();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bEverClicked;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* RowButton;

	

private:
	UCMainMenuWidget* ParentWidget;
	uint32 SelfIndex;
};
