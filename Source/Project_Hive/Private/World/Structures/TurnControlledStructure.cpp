// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "World/Structures/TurnControlledStructure.h"

#include "Game/TurnBasedGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATurnControlledStructure::BeginPlay()
{
	Super::BeginPlay();

	if (const auto GameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		//GameMode->OnPlanningPhaseStartedEvent().AddUObject(this, &ATurnControlledStructure::OnPlanningPhaseStarted);
		//GameMode->OnExecutionPhaseStartedEvent().AddUObject(this, &ATurnControlledStructure::OnExecutionPhaseStarted);
		GameMode->OnPlanningPhaseStarted.AddDynamic(this, &ATurnControlledStructure::OnPlanningPhaseStarted);
		GameMode->OnExecutionPhaseStarted.AddDynamic(this, &ATurnControlledStructure::OnExecutionPhaseStarted);
	}
}
