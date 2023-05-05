// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TicTacToePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int ID;


	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
		int GetID();
	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
		void SetID(int id_novo);
};
