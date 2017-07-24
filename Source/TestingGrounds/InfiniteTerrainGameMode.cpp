// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"


UActorPool* AInfiniteTerrainGameMode::GetNavMeshBoundsVolumePool() const
{
	return NavMeshVolumePool;
}

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator) // return true if iterator points to a suitable actor, false if it has reached the end (Line #305 EngineUtils.h)
	{
		Add(*VolumeIterator); // *VolumeIterator is passing the content of TActorIterator<ANavMeshBoundsVolume> which is *ANavMeshBoundsVolume
		++VolumeIterator; // Iterates to next suitable actor.(Line #241 EngineUtils.h)
	}
}


void AInfiniteTerrainGameMode::Add(ANavMeshBoundsVolume* VolumeToAdd)
{
	NavMeshVolumePool->Add(VolumeToAdd);
}

