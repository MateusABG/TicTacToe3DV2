// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void Server_Reset(const TArray<ATIcTacToePosition*>& position); 

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void Server_Quit(FName MapPath);
};
