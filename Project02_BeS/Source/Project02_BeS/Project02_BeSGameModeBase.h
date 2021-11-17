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

	FVector spawnA;
	FVector spawnB;
	FVector spawnC;
	FRotator spawnRotation;
	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AEnemyFighterCharacter> enemyBP;

	TArray<AEnemyFighterCharacter*> horde;
	void spawn(int count);
	UFUNCTION()
	void spawnWave(int count, int waves);
	FTimerHandle waveHandle;
	int targetScore;
	int enemiesAlive;

	UPROPERTY(VisibleAnywhere)
	int playerScore;
	
	UFUNCTION()
	void updateScore();


};
