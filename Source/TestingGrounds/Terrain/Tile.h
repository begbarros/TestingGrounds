// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

USTRUCT()
struct FSpawnParameters
{
	GENERATED_USTRUCT_BODY()

public:
	FVector SpawnPoint;
	float Yaw = 0;
	float Scale = 1;

};

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void PlaceActors( TSubclassOf<AActor> ToBeSpawned, float Radius = 500 , int32 Min = 1, int32 Max = 1, float MinScale = 1, float MaxScale = 1);


	UFUNCTION(BlueprintCallable, Category = "Setup")
	 void SetPool(UActorPool* InNavMeshVolumePool);	

	UFUNCTION(BlueprintCallable, Category = "AI")
	void PlaceAI(TSubclassOf<APawn> PawnToBeSpawned, float DistanceToOtherObject = 500, int32 Min = 1, int32 Max = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CanSpawnAt(FVector Location, float Radius);

	bool FindFreeSpace(FVector& OutSpawnPoint, float Radius);

	AActor* PlaceActor(TSubclassOf<AActor> ToBeSpawned, FSpawnParameters SpawnParams);

private:

	UActorPool* NavMeshVolumePool;

	AActor* NavMeshVolume;
	
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FVector MinExtent;

	FVector MaxExtent;

	void PositionNavMeshBoundsVolume();
	
	TArray<FSpawnParameters> GenerateValidPositions(int32 Amount, float Scale, float Radius);
};
