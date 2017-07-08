// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get PatrolPoints
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto PatrollingGuard = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = PatrollingGuard->FindComponentByClass<UPatrollingComponent>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) 
	{
		UE_LOG(LogTemp,Warning,TEXT("Tehe is no patrol points in %s"), *(PatrollingGuard->GetName()))
		return EBTNodeResult::Failed; 
	}

	//Set Waypoint in Blackboard
	auto NextIndex = BlackboardComponent->GetValueAsInt(NextIndexKey.SelectedKeyName);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[NextIndex]);
	
	//Cycle Index
	NextIndex = (NextIndex + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(NextIndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}

