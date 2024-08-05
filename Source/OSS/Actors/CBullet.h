#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class OSS_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBullet();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly)
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly)
	UProjectileMovementComponent* MoveComp;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	UParticleSystem* ImpactVFX;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	USoundCue* ImpactSound;
};
