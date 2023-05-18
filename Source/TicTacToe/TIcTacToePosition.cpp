// Fill out your copyright notice in the Description page of Project Settings.

#include "TIcTacToePosition.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATIcTacToePosition::ATIcTacToePosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh Component"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Game/TrainingRoom/Meshes/training_board_cube.training_board_cube"));
	CubeMeshComponent->SetStaticMesh(CubeMeshAsset.Object);
	CubeMeshComponent->SetMaterial(0, TextureNo);
	RootComponent = CubeMeshComponent;

}
void ATIcTacToePosition::ChangeMaterial(int32 Piece)
{
	if (Piece == 1) { 
		CubeMeshComponent->SetMaterial(0, TextureX);
	}
	else if(Piece==2) { 
		CubeMeshComponent->SetMaterial(0, TextureO);
	}
	else if(Piece == 0) {
		CubeMeshComponent->SetMaterial(0, TextureNo);
	}

}
// Called when the game starts or when spawned
void ATIcTacToePosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATIcTacToePosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

