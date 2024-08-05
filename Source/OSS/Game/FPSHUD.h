// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

class UCPlayerStatusWidget;

UCLASS()
class AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	//Player Status Widget
private:
	TSubclassOf<UCPlayerStatusWidget> PlayerStatusWidgetClass;

	UCPlayerStatusWidget* PlayerStatusWidget;
};

