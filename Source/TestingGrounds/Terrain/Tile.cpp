// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include  "DrawDebugHelpers.h"

#define OUT

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::PlaceActors( TSubclassOf<AActor> ToBeSpawned, float Radius, int32 Min, int32 Max, float MinScale, float MaxScale)
{
	//TODO Get Radius for actor
	
	auto Amount = FMath::RandRange(Min, Max);
	for (int i = 0; i < Amount; i++)
	{
		auto RandomScale = FMath::RandRange(MinScale, MaxScale);
		FVector SpawnPoint;
		if (FindFreeSpace(OUT SpawnPoint, Radius * RandomScale)) 
		{
			float RandomYaw = FMath::RandRange(-180, 180);
			PlaceActor(ToBeSpawned, SpawnPoint, RandomYaw , RandomScale);
		}
	}
	/*FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	auto Amount = FMath::RandRange(min, max);
	for (int32 i = 0; i < Amount; i++)
	{
		auto SpawnedPoint = FMath::RandPointInBox(Bounds);
		auto SpawnedObject = GetWorld()->SpawnActor<AActor>(ToBeSpawned);
		SpawnedObject->SetActorRelativeLocation(SpawnedPoint);
		SpawnedObject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
	}*/

}

bool ATile::FindFreeSpace(FVector & OutSpawnPoint, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	int const MAX_ATTEMPTS = 100;
	for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++)
	{
		auto CandidateSpawnPoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAt(CandidateSpawnPoint, Radius))
		{
			OutSpawnPoint = CandidateSpawnPoint;
			return true;
		}
	}
	return false;
}

bool ATile::CanSpawnAt(FVector CandidateLocation, float Radius)
{
	FHitResult Hit;
	auto CandidateWorldLocation = ActorToWorld().TransformPosition(CandidateLocation);
	bool bHitSomething = GetWorld()->SweepSingleByChannel(
		Hit,
		CandidateWorldLocation,
		CandidateWorldLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Spawn Channel defined in /Config/DefaultEngine.ini 
		FCollisionShape::MakeSphere(Radius)
	);
	//bHitSomething ? DrawDebugSphere(GetWorld(), CandidateWorldLocation, Radius, 8, FColor::Red, true) : DrawDebugSphere(GetWorld(), CandidateWorldLocation, Radius, 12, FColor::Green, true); 
	
	return !bHitSomething;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToBeSpawned, FVector SpawnPoint, float Yaw , float Scale)
{
	auto SpawnedObject = GetWorld()->SpawnActor<AActor>(ToBeSpawned);
	SpawnedObject->SetActorRelativeLocation(SpawnPoint);
	SpawnedObject->SetActorRotation(FRotator(0, Yaw, 0));
	SpawnedObject->SetActorScale3D(FVector(Scale));
	SpawnedObject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}



