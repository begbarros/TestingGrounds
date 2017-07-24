// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{

}

AActor * UActorPool::RetrieveFromPool()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
		UE_LOG(LogTemp,Error,TEXT("There is no Actor in the pool"))
	}
	else
	{ 
		
		auto NavMeshBoundsVolumeRetrieved = Pool.Pop(); 
		UE_LOG(LogTemp, Warning, TEXT("%s Retrieved from pool"), *(NavMeshBoundsVolumeRetrieved->GetName()))
		return NavMeshBoundsVolumeRetrieved;
	}
}

void UActorPool::ReturnActorToPool(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s returning to the pool"),*(Actor->GetName()))
	Add(Actor);
}

void UActorPool::Add(AActor*Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s added to the pool"), *(Actor->GetName()))
	Pool.Push(Actor);
}
