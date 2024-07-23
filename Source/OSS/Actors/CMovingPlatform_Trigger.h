#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMovingPlatform_Trigger.generated.h"

class UBoxComponent;
class ACMovingPlatform;

UCLASS()
class OSS_API ACMovingPlatform_Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMovingPlatform_Trigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(EditInstanceOnly, Category = "MovingPlatform")
	TArray<ACMovingPlatform*> PlatformsToTrigger;
};
