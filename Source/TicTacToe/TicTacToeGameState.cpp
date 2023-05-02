// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToeGameState.h"
#include "TIcTacToePosition.h"
#include "TIcTacToeProjectile.h"


bool checkWin(char matrix[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player)
        {
            return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player)
        {
            return true;
        }
    }

    if (matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player)
    {
        return true;
    }

    if (matrix[0][2] == player && matrix[1][1] == player && matrix[2][0] == player)
    {
        return true;
    }
    return false;
}

bool checkTie(char matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == NULL) {
                return false;
            }
        }
    }
    return true;
}
 

FString printTable(char matrix[3][3]) {
    FString text; 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == NULL) {
                text += "_";
            }
            else {
                text += matrix[i][j];
            }
        }
        text += "\n";
    }
    return text;
}

void ATicTacToeGameState::Server_Shoot_Implementation(FRotator SpawnRotator,FVector SpawnLocation) {   
   GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Shoot Server"));
     UWorld* const World = GetWorld(); 
     FActorSpawnParameters ActorSpawnParams;
     ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
     World->SpawnActor<ATicTacToeProjectile>(ProjectileClass, SpawnLocation, SpawnRotator, ActorSpawnParams);
}

void ATicTacToeGameState::Multicast_Shoot_Implementation(FRotator SpawnRotator, FVector SpawnLocation) {
   GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Shoot Client"));
   UWorld* const World = GetWorld();
   FActorSpawnParameters ActorSpawnParams;
   ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
   World->SpawnActor<ATicTacToeProjectile>(ProjectileClass, SpawnLocation, SpawnRotator, ActorSpawnParams);
}

void ATicTacToeGameState::Server_InputBlockPosition_Implementation(const FString& positions, int index) {  
    inputBlockPosition(positions, index);
}

void ATicTacToeGameState::Server_ChangeMaterial_Implementation(ATIcTacToePosition* pos, int playerIndex) {
    ChangeMaterial(pos, playerIndex);
}


void ATicTacToeGameState::inputBlockPosition(FString positions, int playerIndex)
{ 
    TArray<FString> Substrings;
    positions.ParseIntoArray(Substrings, TEXT(","), true);

    if (Substrings.Num() == 2) {
        int X = FCString::Atoi(*Substrings[0]);
        int Y = FCString::Atoi(*Substrings[1]); 

        if (playerIndex == 1) {
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'X';
                bool won = checkWin(matrix, 'X');
                bool tied = checkTie(matrix);
                if (won) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "X wins");
                }
                else if (tied) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tied"));
                }
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Poscao jah pega, jogue de novo"));
            }
        }
        else {
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'O';
                bool won = checkWin(matrix, 'O');
                bool tied = checkTie(matrix);
                if (won) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("O wins"));
                }
                else if (tied) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tied"));
                }
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Poscao jah pega, jogue de novo"));
            }
        }

        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, printTable(matrix));
        if (whichPlayer == 1) {
            whichPlayer = 2;
        }
        else {
            whichPlayer = 1;
        }
    }
}
void ATicTacToeGameState::ChangeMaterial(ATIcTacToePosition* pos,int playerIndex)
{
    pos->ChangeMaterial(playerIndex);
}
 
 