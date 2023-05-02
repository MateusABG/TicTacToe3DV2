// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "CoreMinimal.h" 
#include "GameFramework/Actor.h"
#include "TicTacToeCubePosition.generated.h"

UCLASS()
class TICTACTOE_API ATicTacToeCubePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATicTacToeCubePosition(); 

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshX;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* MeshO;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
