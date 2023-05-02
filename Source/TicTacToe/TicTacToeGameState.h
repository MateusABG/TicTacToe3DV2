// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TIcTacToePosition.h"
#include "TicTacToeGameState.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	char matrix[3][3];
	//Pode ser adicionado ao mundo?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameState")
		bool canSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameState")
		int whichPlayer = 1;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ATicTacToeProjectile> ProjectileClass;

	UFUNCTION(Server, Reliable)
		void Server_InputBlockPosition(const FString& position, int playerIndex);

	UFUNCTION(Server, Reliable)
		void Server_ChangeMaterial(ATIcTacToePosition* pos, int playerIndex);

	UFUNCTION(Server, Reliable)
		void Server_Shoot(FRotator SpawnRotation,FVector SpawnLocation);

	UFUNCTION(NetMulticast, Unreliable)
		void Multicast_Shoot(FRotator SpawnRotation, FVector SpawnLocation);

protected:  
	//Coloca objeto na posi��o
		void inputBlockPosition(FString positions, int playerIndex);
	 
		//Muda Material do Objeto
		void ChangeMaterial(ATIcTacToePosition* pos, int playerIndex);
};
