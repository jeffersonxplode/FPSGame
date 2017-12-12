// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	
	//UE_LOG(LogTemp, Warning, TEXT("AI IN C++ YAY"));

	


	//Get the patrol points

	
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) {	return EBTNodeResult::Failed; }



	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) {

		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing Patrol Points"));
	}



	//Set Next Waypoint

	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto IndexKey = BlackBoardComp->GetValueAsInt(Index.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(Waypointkey.SelectedKeyName, PatrolPoints[IndexKey]);
	

	//Cycle Index

	auto NextIndex = (IndexKey + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(Index.SelectedKeyName, NextIndex);


	// TODO protect Agains empty Patrol routes



	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), IndexKey);

	return EBTNodeResult::Succeeded;

}

