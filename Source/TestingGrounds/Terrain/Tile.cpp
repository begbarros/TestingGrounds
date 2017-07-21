// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include  "DrawDebugHelpers.h"


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
	SphereCast(GetActorLocation(), 500);
}

bool ATile::SphereCast(FVector Location, float Radius)
{
	FHitResult Hit;
	bool bHitSomething = GetWorld()->SweepSingleByChannel(
		Hit,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Spawn Channel defined in /Config/DefaultEngine.ini 
		FCollisionShape::MakeSphere(Radius)
	);
	bHitSomething ? DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Red, true) : DrawDebugSphere(GetWorld(), Location, Radius, 12, FColor::Green, true); 
	
	return bHitSomething;
}

void ATile::PlaceActor( TSubclassOf<AActor> ToBeSpawned, int32 min, int32 max)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	auto Amount = FMath::RandRange(min, max);
	for (int32 i = 0; i < Amount; i++)
	{
		auto SpawnedPoint = FMath::RandPointInBox(Bounds);
		auto SpawnedObject = GetWorld()->SpawnActor<AActor>(ToBeSpawned);
		SpawnedObject->SetActorRelativeLocation(SpawnedPoint);
		SpawnedObject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
	}
}
// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

