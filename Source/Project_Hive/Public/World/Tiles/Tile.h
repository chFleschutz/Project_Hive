// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cube.h"
#include "World/Structures/TileStructure.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class ATileStructure;
class ANavigationCharacter;

UCLASS()
class PROJECT_HIVE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the position in the grid
	void SetGridPosition(const FCube& Position);
	FCube GetGridPosition() { return GridPosition; }

	void AddNeighbor(ATile* Neighbor);

	// Renders a highlight outline 
	void SetSelected(bool IsSelected) const;

	virtual bool CanBuild();

	virtual bool CanBuild(ATileStructure* NewStructure);
	virtual void Build(ATileStructure* NewStructure);
	
	bool CanDestroyBuilding() const;
	void DestroyBuilding();

	virtual bool CanTakeCharacter();
	bool TakeCharacter(ANavigationCharacter* NewCharacter);
	ANavigationCharacter* GetCharacter() const { return Character; }

	TArray<ATile*> GetNeighbors() { return Neighbors; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	// Hexagon Static Mesh Component 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Mesh")
		class UStaticMeshComponent* HexTileMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		EFoundationType TileFoundationType;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		ATileStructure* Structure = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		ANavigationCharacter* Character = nullptr;

	FCube GridPosition;
	TArray<ATile*> Neighbors;
};
