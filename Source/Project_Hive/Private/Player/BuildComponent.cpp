// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "Player/BuildComponent.h"

#include "Engine/DataTable.h"
#include "Player/BirdsEyePlayerController.h"
#include "World/Structures/PreviewStructure.h"
#include "World/Structures/TileStructure.h"
#include "World/Tiles/Tile.h"


// Sets default values for this component's properties
UBuildComponent::UBuildComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called every frame
void UBuildComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PreviewStructure)
	{
		UpdatePreview();
	}
}

void UBuildComponent::ShowPreview(const FStructureData& StructureData)
{
	if (PreviewStructure)
		HidePreview();

	PreviewData = StructureData;

	if (const auto World = GetWorld())
	{
		const auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
		PreviewStructure = World->SpawnActor<APreviewStructure>(PreviewStructureClass, FVector::Zero(), Rotation);
		if (!PreviewStructure)
			return;

		PreviewStructure->SetMesh(PreviewData.Mesh);
		UpdatePreview();
	}
}

void UBuildComponent::HidePreview()
{
	PreviewStructure->Destroy();
	PreviewStructure = nullptr;
}

bool UBuildComponent::BuildStructure()
{
	// Spawn Actor
	const auto World = GetWorld();
	if (!World)
		return false;

	const auto PlayerController = Cast<ABirdsEyePlayerController>(World->GetFirstPlayerController());
	if (!PlayerController)
		return false;

	if (const auto Tile = PlayerController->QueryTileUnderCursor())
	{
		if (!IsBuildLocationValid(Tile))
			return false;

		const auto Rotation = PreviewStructure->GetActorRotation();
		const auto Location = Tile->GetCenterSocketLocation();
		const auto Structure = World->SpawnActor<ATileStructure>(PreviewData.StructureClass, Location, Rotation);
		Structure->SetStructureData(PreviewData);
		Tile->Build(Structure);
	}

	HidePreview();
	return true;
}

// Called when the game starts
void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();
	if (StructuresTable)
		StructuresTable->GetAllRows<FStructureData>("BuildComponent", BuildableStructures);
}

void UBuildComponent::UpdatePreview() const
{
	const auto World = GetWorld();
	if (!World)
		return;
	const auto PlayerController = Cast<ABirdsEyePlayerController>(World->GetFirstPlayerController());
	if (!PlayerController)
		return;

	if (const auto Tile = PlayerController->QueryTileUnderCursor())
	{
		PreviewStructure->SetPreviewState(IsBuildLocationValid(Tile));
		PreviewStructure->SetActorLocation(Tile->GetCenterSocketLocation());
	}
}

bool UBuildComponent::IsBuildLocationValid(const ATile* Tile) const
{
	if (!Tile)
		return false;

	const bool HasStructure = Tile->GetStructure() != nullptr;
	const bool HasSupportedFoundation = PreviewData.SupportedFoundationTypes.Contains(Tile->GetType());
	return !HasStructure && HasSupportedFoundation;
}
