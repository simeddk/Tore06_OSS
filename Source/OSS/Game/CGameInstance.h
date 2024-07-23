#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

class UUserWidget;

UCLASS()
class OSS_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();
	virtual void Init() override;

public:
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& InAddress);

	UFUNCTION(BlueprintCallable, Exec)
	void LoadMainMenu();

private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
