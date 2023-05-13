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
		void Server_InputBlockPosition(ATIcTacToePosition* pos,const FString& position, int playerIndex);

	UFUNCTION(Server, Reliable)
		void Server_ChangeMaterial(ATIcTacToePosition* pos, int playerIndex);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_ChangeMaterial(ATIcTacToePosition* pos, int playerIndex);

	UFUNCTION(Server, Reliable)
		void Server_Shoot(UWorld* world, FRotator SpawnRotation,FVector SpawnLocation);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_Shoot(UWorld* world,FRotator SpawnRotation, FVector SpawnLocation);

	
		void Server_Reset(const TArray<ATIcTacToePosition*>& position);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
		void Multicast_Reset(const TArray<ATIcTacToePosition*>& position);


	void Server_QuitGame(FName MapPath);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
		void Multicast_QuitGame(FName MapPath);
	 
	void Server_Pause_Game();
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
		void Multicast_Pause_Game();

	bool won = false;
	UPROPERTY(BlueprintReadWrite)
		bool Xwon = false;
	UPROPERTY(BlueprintReadWrite)
		bool Owon = false;
	UPROPERTY(BlueprintReadWrite)
		bool tied = false;
protected:  
	//Coloca objeto na posição
		void inputBlockPosition(ATIcTacToePosition* pos,FString positions, int playerIndex);
	 
		//Muda Material do Objeto
		void ChangeMaterial(ATIcTacToePosition* pos, int playerIndex);


		 
};
