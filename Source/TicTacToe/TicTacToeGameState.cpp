// Fill out your copyright notice in the Description page of Project Settings.
 
#include "TicTacToeGameState.h"
#include "TIcTacToePosition.h" 
#include "TIcTacToeProjectile.h" 
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"

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

void ATicTacToeGameState::Server_QuitGame(FName MapPath) {
    Multicast_QuitGame(MapPath);
}

void ATicTacToeGameState::Multicast_QuitGame_Implementation(FName MapPath) {
    UWorld* world = GetWorld(); 
    UGameplayStatics::OpenLevel(world, MapPath);
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
    Xwon = false;
    Owon = false;
    won = false;
    tied = false;
}


void ATicTacToeGameState::Server_Pause_Game() {

}
void ATicTacToeGameState::Multicast_Pause_Game_Implementation() {

}
 

void ATicTacToeGameState::inputBlockPosition(ATIcTacToePosition* pos,FString positions, int playerIndex)
{ 
    TArray<FString> Substrings;
    positions.ParseIntoArray(Substrings, TEXT(","), true);

    if (Substrings.Num() == 2) {
        int X = FCString::Atoi(*Substrings[0]);
        int Y = FCString::Atoi(*Substrings[1]); 
        if (playerIndex == 1 && playerIndex==whichPlayer && (Xwon==false && tied == false)) {
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'X';
                Xwon = checkWin(matrix, 'X');
                tied=checkTie(matrix);
                if (Xwon || tied) {     
                    GameOver(); 
                } 
                Server_ChangeMaterial(pos,playerIndex);
                whichPlayer = 2;
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Posicao jah pega, jogue de novo"));
            }
        }
        else if(playerIndex==2 && playerIndex == whichPlayer && (Owon == false && tied == false)){
            if (matrix[X][Y] == NULL) {
                matrix[X][Y] = 'O';
                Owon = checkWin(matrix, 'O');
                tied=checkTie(matrix);
                if (Owon || tied){
                    GameOver(); 
                } 
                Server_ChangeMaterial(pos, playerIndex);
                whichPlayer = 1;
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Posicao jah pega, jogue de novo"));
            }
        } 
        
    }
}
void ATicTacToeGameState::ChangeMaterial(ATIcTacToePosition* pos,int playerIndex)
{  
        pos->ChangeMaterial(playerIndex); 
    
}
 
void ATicTacToeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATicTacToeGameState, Xwon);
    DOREPLIFETIME(ATicTacToeGameState, Owon);
    DOREPLIFETIME(ATicTacToeGameState, tied);
}