#include "CMovingPlatform_Trigger.h"
#include "Components/BoxComponent.h"
#include "../OSS.h"
#include "CMovingPlatform.h"

ACMovingPlatform_Trigger::ACMovingPlatform_Trigger()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;
}

void ACMovingPlatform_Trigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACMovingPlatform_Trigger::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACMovingPlatform_Trigger::OnEndOverlap);
}

void ACMovingPlatform_Trigger::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//LogOnScreen(this, GetNameSafe(OtherActor) + " is begin overlap");

	for (const auto& Platform : PlatformsToTrigger)
	{
		Platform->IncreaseActiveCount();
	}
}

void ACMovingPlatform_Trigger::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//LogOnScreen(this, GetNameSafe(OtherActor) + " is end overlap");

	for (const auto& Platform : PlatformsToTrigger)
	{
		Platform->DecreaseActiveCount();
	}
}
