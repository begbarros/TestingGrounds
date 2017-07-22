// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void PlaceActors( TSubclassOf<AActor> ToBeSpawned , int32 min, int32 max);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CanSpawnAt(FVector Location, float Radius);

	bool FindFreeSpace(FVector& OutSpawnPoint, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToBeSpawned, FVector SpawnPoint);

private:


	
	
};
