// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterCharacter.h"

#include "EnemyFighterCharacter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZombieDeath, int, index);

UCLASS()
class PROJECT02_BES_API AEnemyFighterCharacter : public AFighterCharacter
{
	GENERATED_BODY()

public:
	AEnemyFighterCharacter();
	UFUNCTION(BlueprintCallable)
		void enableWalking();
	UFUNCTION(BlueprintCallable)
		void disableWalking();
	UFUNCTION(BlueprintCallable)
		void startAttack();
	UFUNCTION(BlueprintCallable)
		void endAttack();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = State)
		bool attack;

	virtual void handleDeath();

	int index;
	void setIndex(int idNum);


	UPROPERTY(BlueprintAssignable, Category = "EventsDelegates")
		FZombieDeath OnDeath;


};
