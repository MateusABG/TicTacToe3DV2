// Fill out your copyright notice in the Description page of Project Settings.

 
#include "Kismet/GameplayStatics.h"
#include "TicTacToePlayerController.h"
#include <TicTacToe/TicTacToeGameState.h>

void ATicTacToePlayerController::Server_Reset_Implementation(const TArray<ATIcTacToePosition*>& position)
{
	ATicTacToeGameState* gamestate = Cast<ATicTacToeGameState>(UGameplayStatics::GetGameState(this));
	gamestate->Server_Reset(position);
}

void ATicTacToePlayerController::Server_Quit_Implementation(FName MapPath) {
	ATicTacToeGameState* gamestate = Cast<ATicTacToeGameState>(UGameplayStatics::GetGameState(this));
	UWorld* world = GetWorld();
	gamestate->Server_QuitGame(MapPath);
}