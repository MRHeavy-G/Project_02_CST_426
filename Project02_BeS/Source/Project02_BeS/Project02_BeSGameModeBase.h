// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "EnemyFighterCharacter.h"


#include "GameFramework/GameModeBase.h"
#include "Project02_BeSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT02_BES_API AProject02_BeSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;

private:

	FVector locaA;
	FVector locaB;
	FVector locaC;
	FVector spawnOutLoc;
	FRotator spawnRotation;
	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AEnemyFighterCharacter> enemyBP;

	TArray<AEnemyFighterCharacter*> horde;
	void spawnIn(FVector location);

	void spawnOut(int index);
	UFUNCTION()
	void spawnWave(int count, int waves);
	FTimerHandle waveHandle;
	int targetScore;
	int enemiesAlive;

	UPROPERTY(VisibleAnywhere)
	int playerScore;
	
	UFUNCTION()
	void updateScore(int index);


};
