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

void ATicTacToeGameState::Server_Shoot_Implementation(UWorld* world, FRotator SpawnRotator,FVector SpawnLocation) { 
   Multicast_Shoot(world,SpawnRotator, SpawnLocation);
}

void ATicTacToeGameState::Multicast_Shoot_Implementation(UWorld* world, FRotator SpawnRotator, FVector SpawnLocation) { 
   
   FActorSpawnParameters ActorSpawnParams;
   ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
   world->SpawnActor<ATicTacToeProjectile>(ProjectileClass, SpawnLocation, SpawnRotator, ActorSpawnParams);
}

void ATicTacToeGameState::Server_InputBlockPosition_Implementation(ATIcTacToePosition* pos,const FString& positions, int index) {
    inputBlockPosition(pos,positions, index);
}

void ATicTacToeGameState::Server_ChangeMaterial_Implementation(ATIcTacToePosition* pos, int playerIndex) {
    Multicast_ChangeMaterial(pos,playerIndex);
}

void ATicTacToeGameState::Multicast_ChangeMaterial_Implementation(ATIcTacToePosition* pos, int playerIndex) {

        ChangeMaterial(pos, playerIndex);
}

 

void ATicTacToeGameState::Server_Reset(const TArray<ATIcTacToePosition*>& position)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = NULL;
        }
    }
    Multicast_Reset(position);
}

void ATicTacToeGameState::Multicast_Reset_Implementation(const TArray<ATIcTacToePosition*>& position)
{

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = NULL;
        }
    }

    for (int i = 0; i < position.Num(); i++) {
        position[i]->ChangeMaterial(0);
    }
    whichPlayer = 1;


}

void ATicTacToeGameState::inputBlockPosition(ATIcTacToePosition* pos,FString positions, int playerIndex)
{ 
    TArray<FString> Substrings;
    positions.ParseIntoArray(Substrings, TEXT(","), true);

    if (Substrings.Num() == 2) {
        int X = FCString::Atoi(*Substrings[0]);
        int Y = FCString::Atoi(*Substrings[1]); 
        if (playerIndex == 1 && playerIndex==whichPlayer && (won==false && tied == false)) {
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'X';
                won = checkWin(matrix, 'X');
                tied = checkTie(matrix);
                if (won) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "X wins");
                }
                else if (tied) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tied"));
                }
                Server_ChangeMaterial(pos,playerIndex);
                whichPlayer = 2;
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Poscao jah pega, jogue de novo"));
            }
        }
        else if(playerIndex==2 && playerIndex == whichPlayer && (won == false && tied == false)){
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'O';
                won = checkWin(matrix, 'O');
                tied = checkTie(matrix);
                if (won) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("O wins"));
                }
                else if (tied) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tied"));
                }
                Server_ChangeMaterial(pos, playerIndex);
                whichPlayer = 1;
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Poscao jah pega, jogue de novo"));
            }
        } 
        
    }
}
void ATicTacToeGameState::ChangeMaterial(ATIcTacToePosition* pos,int playerIndex)
{  
        pos->ChangeMaterial(playerIndex); 
    
}
 
 