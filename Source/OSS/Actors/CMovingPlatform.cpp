#include "CMovingPlatform.h"

ACMovingPlatform::ACMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	
	Speed = 100.f;
	ActiveCount = 1;
}

void ACMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartWS = GetActorLocation();
	TargetWS = GetTransform().TransformPosition(TargetLS);
}

void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveCount > 0)
	{
		if (HasAuthority())
		{
			FVector CurrentLocation = GetActorLocation();

			float TotalDistance = (StartWS - TargetWS).Size();
			float CurrentDistance = (CurrentLocation - StartWS).Size();

			if (CurrentDistance >= TotalDistance)
			{
				FVector Temp = StartWS;
				StartWS = TargetWS;
				TargetWS = Temp;
			}

			FVector Direction = (TargetWS - StartWS).GetSafeNormal();

			CurrentLocation += Direction * Speed * DeltaTime;
			SetActorLocation(CurrentLocation);
		}
	}
}

void ACMovingPlatform::IncreaseActiveCount()
{
	ActiveCount++;
}

void ACMovingPlatform::DecreaseActiveCount()
{
	if (ActiveCount > 0)
	{
		ActiveCount--;
	}
}
