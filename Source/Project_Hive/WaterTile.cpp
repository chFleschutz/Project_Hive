// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterTile.h"

bool AWaterTile::CanBuild()
{
    return false;
}

void AWaterTile::Build(TSubclassOf<ATileStructure> structure)
{
    // Not able to build
}
