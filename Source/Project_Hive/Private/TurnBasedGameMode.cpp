// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameMode.h"


ATurnBasedGameMode::ATurnBasedGameMode()
{
}

void ATurnBasedGameMode::PlayerFinishedTurn()
{
	NumPlayerReady++;
	if (NumPlayerReady < GetNumPlayers())
		return;

	StartExecutionPhase();
}

void ATurnBasedGameMode::ExecutionStarted()
{
	NumExecuting++;
}

void ATurnBasedGameMode::ExecutionFinished()
{
	NumExecuting--;
	if (NumExecuting != 0)
		return;

	StartPlanningPhase();
}

void ATurnBasedGameMode::StartPlanningPhase()
{
	GamePhase = EGamePhase::GP_Planning;
	NumPlayerReady = 0;
	PlanningPhaseEvent.Broadcast();
}

void ATurnBasedGameMode::StartExecutionPhase()
{
	GamePhase = EGamePhase::GP_Executing;
	NumExecuting = 0;

	ExecutionStarted();
	ExecutionPhaseEvent.Broadcast();
	ExecutionFinished();
}
