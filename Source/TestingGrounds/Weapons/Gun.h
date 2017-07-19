// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:
	USceneComponent* GetMuzzleLocation() const;

	UFUNCTION(BlueprintCallable, Category= Firing)
	void OnFire();

	UAnimInstance* AnimInstance1P;

	UAnimInstance* AnimInstanceTP;


protected:
	AGun();

	UPROPERTY(VisibleDefaultsOnly, Category = Muzzle)
	USkeletalMeshComponent* Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Muzzle)
	USceneComponent* MuzzleLocation;
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimationTP;
	
	
};
