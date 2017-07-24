// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include  "DrawDebugHelpers.h"
#include "../ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"

#define OUT

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	if (NavMeshVolumePool)
	{
		NavMeshVolume = NavMeshVolumePool->RetrieveFromPool();
		PositionNavMeshBoundsVolume();
	}
}

void ATile::SetPool(UActorPool * InNavMeshVolumePool)
{
	NavMeshVolumePool = InNavMeshVolumePool;
}

void ATile::PlaceActors( TSubclassOf<AActor> ToBeSpawned, float Radius, int32 Min, int32 Max, float MinScale, float MaxScale)
{
	
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

}

bool ATile::FindFreeSpace(FVector & OutSpawnPoint, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);
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

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (NavMeshVolumePool) { NavMeshVolumePool->ReturnActorToPool(NavMeshVolume); }
}

void ATile::PositionNavMeshBoundsVolume()
{
	
	if (NavMeshVolume == nullptr) { return; }
	NavMeshVolume->SetActorLocation(GetActorLocation());
	GetWorld()->GetNavigationSystem()->Build();
}



