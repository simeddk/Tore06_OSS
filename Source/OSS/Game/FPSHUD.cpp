// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "../UI/CPlayerStatusWidget.h"

AFPSHUD::AFPSHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	static ConstructorHelpers::FClassFinder<UCPlayerStatusWidget> WidgetClass(TEXT("/Game/UI/WB_PlayerStatus"));
	if (WidgetClass.Succeeded())
	{
		PlayerStatusWidgetClass = WidgetClass.Class;
	}
}


void AFPSHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(PlayerStatusWidgetClass))
	{
		PlayerStatusWidget = CreateWidget<UCPlayerStatusWidget>(GetWorld(), PlayerStatusWidgetClass);
		PlayerStatusWidget->AddToViewport();
	}
}

/** This method draws a very simple crosshair */
void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	// Find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// Offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );

	// Draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

