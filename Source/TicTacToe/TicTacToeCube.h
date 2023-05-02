// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TicTacToeCube.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UTicTacToeCube : public UStaticMeshComponent
{
	GENERATED_BODY()


		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshX;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshO;
	
};
