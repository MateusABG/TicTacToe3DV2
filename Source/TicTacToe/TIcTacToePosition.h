// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIcTacToePosition.generated.h"

UCLASS()
class TICTACTOE_API ATIcTacToePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATIcTacToePosition();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CubeMeshComponent;
	UMaterialInstanceDynamic* CubeMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* TextureX;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* TextureO;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* TextureNo;
	UPROPERTY(EditAnywhere)
		FString Position;

	void ChangeMaterial(int32 Piece);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
