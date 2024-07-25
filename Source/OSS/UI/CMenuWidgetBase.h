#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Game/CMenuInterface.h"
#include "CMenuWidgetBase.generated.h"

UCLASS()
class OSS_API UCMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetOwningInstance(ICMenuInterface* InOwningInstance);
	void SetInputToUI();
	void SetInputToGame();

protected:
	ICMenuInterface* OwningInstance;
};
