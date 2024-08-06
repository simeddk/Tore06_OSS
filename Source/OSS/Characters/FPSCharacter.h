#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Game/CPlayerState.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;
class UParticleSystemComponent;
class ACBullet;

UCLASS(config=Game)
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* FP_Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* TP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Muzzle)
	UParticleSystemComponent* FP_GunshotParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = Muzzle)
	UParticleSystemComponent* TP_GunshotParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

public:
	AFPSCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FP_FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* TP_FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponDamage;

protected:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Fire
protected:
	void OnFire();

private:
	UFUNCTION(Server, Unreliable)
	void ServerFire(const FVector& LineStart, const FVector& LineEnd);

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticastFire();

	//Crouch
protected:
	void ToggleCrouch();

	UFUNCTION(Server, Unreliable)
	void ServerToggleCrouch();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsCrouch() const { return bCrouch; }

private:
	UPROPERTY(ReplicatedUsing = "OpRep_bCrouch")
	bool bCrouch;

	UFUNCTION()
	void OpRep_bCrouch();
	void CrouchMovement();

	//Health
private:
	UPROPERTY(Replicated)
	float Health;

public:
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }

private:
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticastRagdoll(FVector ImpactDirection);

	UFUNCTION(Client, Unreliable)
	void ClientRagdoll(FVector ImpactDirection);

	//Team Color
public:
	void SetTeamColor(ETeamType InTeam);

private:
	UPROPERTY(ReplicatedUsing = "OnRep_BodyColor")
	FVector BodyColor;

	UFUNCTION()
	void OnRep_BodyColor();
};

