// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToePlayerState.h"

int ATicTacToePlayerState::GetID() 
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(ID));
	return ID;
}


void ATicTacToePlayerState::SetID(int id_novo)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(ID));
	ID = id_novo;
}
