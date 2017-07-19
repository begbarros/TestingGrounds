// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "BallProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

AGun::AGun()
{
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->bCastDynamicShadow = false;
	Gun->CastShadow = false;
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->AttachToComponent(Gun,FAttachmentTransformRules::KeepRelativeTransform);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

USceneComponent* AGun::GetMuzzleLocation() const
{
	return MuzzleLocation;
}

void AGun::OnFire()
{
	if (ProjectileClass != NULL)
	{
		if (!ensure(MuzzleLocation)) { return; }
		UWorld* const World = GetWorld();
		if (World != NULL)
		{

			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();


			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

		}
	}
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation1P != NULL && AnimInstance1P != NULL)
	{
		AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);

	}
	else if (FireAnimationTP != NULL && AnimInstanceTP != NULL)
	{
		AnimInstanceTP->Montage_Play(FireAnimationTP, 1.f);
	}
}