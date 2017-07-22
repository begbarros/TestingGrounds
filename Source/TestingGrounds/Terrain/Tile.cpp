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

void ATile::PlaceActors( TSubclassOf<AActor> ToBeSpawned, int32 min, int32 max)
{
	//TODO Get Radius for actor
	float Radius = 500;
	auto Amount = FMath::RandRange(min, max);
	for (int i = 0; i < Amount; i++)
	{
		FVector SpawnPoint;
		if (FindFreeSpace(OUT SpawnPoint, Radius)) { PlaceActor(ToBeSpawned, SpawnPoint); }
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
	bHitSomething ? DrawDebugSphere(GetWorld(), CandidateWorldLocation, Radius, 8, FColor::Red, true) : DrawDebugSphere(GetWorld(), CandidateWorldLocation, Radius, 12, FColor::Green, true); 
	
	return !bHitSomething;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToBeSpawned, FVector SpawnPoint)
{
	auto SpawnedObject = GetWorld()->SpawnActor<AActor>(ToBeSpawned);
	SpawnedObject->SetActorRelativeLocation(SpawnPoint);
	SpawnedObject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}



