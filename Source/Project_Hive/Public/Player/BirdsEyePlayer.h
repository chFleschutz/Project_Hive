// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdsEyePlayer.generated.h"

class ATile;
class ATileStructure;
class UInputAction;
class UInputComponent;
struct FInputActionValue;

UCLASS()
class PROJECT_HIVE_API ABirdsEyePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdsEyePlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void BuildOnSelectedTile();

	UFUNCTION(BlueprintCallable)
		void DestroyBuildingOnSelectedTile();

	UFUNCTION(BlueprintCallable)
		bool CanBuild();

	UFUNCTION(BlueprintCallable)
		bool CanDestroyBuilding();

	UFUNCTION(BlueprintCallable)
		bool HasTileSelected();

	UFUNCTION(BlueprintCallable)
		void StartBuildingStructure(TSubclassOf<ATileStructure> Structure);

	UFUNCTION(BlueprintCallable)
		bool CanSpawnCharacter() const;

	UFUNCTION(BlueprintCallable)
		void SpawnCharacter(TSubclassOf<class ANavigationCharacter> Character) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATile* QueryTileUnderCursor() const;

	// Input action callbacks:
	//
	void Zoom(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);
	void MoveToTarget(const FInputActionValue& Value);

	// Components
	//
	/** An invisible Mesh Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Mesh")
		class UStaticMeshComponent* InvisibleMesh;
	
	/** Camera Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera")
		class UCameraComponent* Camera;

	/** Spring Arm Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera")
		class USpringArmComponent* SpringArm;

	/** DefaultPawn movement component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		class UFloatingPawnMovement* MovementComponent;

	// Camera Settings
	//
	/** Min Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float MinCameraZoom = 500.0f;

	/** Max Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float MaxCameraZoom = 2000.0f;

	/** Zoom Speed */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float ZoomSpeed = 100.0f;

	/** Min Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings")
		float MinPitchAngle = 290.0f;

	/** Max Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings")
		float MaxPitchAngle = 360.0f;

	// Game-play
	//
	/** Default Build Structure */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Structure")
		TSubclassOf<ATileStructure> DefaultStructure;

	// Input
	//
	/** Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
		class UInputMappingContext* InputMapping;

	/** Zoom Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* ZoomAction;

	/** Look Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* LookAction;

	/** Move Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* MoveAction;

	/** Select Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* SelectAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* MoveTargetAction;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
	ATile* SelectedTile = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
	ATileStructure* PreviewStructure;
};
