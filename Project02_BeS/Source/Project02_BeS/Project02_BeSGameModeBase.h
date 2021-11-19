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
		 void print();
private:
	//Teleport to Locations
	FVector locaA;
	FVector locaB;
	FVector locaC;
	//inital world spawn 
	FVector spawnOutLoc;
	//initial facing spawn 
	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AEnemyFighterCharacter> enemyBP;
	//list of enemies
	TArray<AEnemyFighterCharacter*> horde;

	//more like teleport to 
	void spawnIn(FVector location);
	// teleport out of sight
	void spawnOut(int index);
	//spawn in a count of zombies every 3 seconds for n waves
	UFUNCTION()
	void spawnWave(int count, int waves);
	FTimerHandle waveHandle;

	//keep track of when next wave is up next 
	int targetScore;
	int enemiesAlive;

	//delegate of event when zombies die, they pass their index in the horde in order to spawn it out
	UFUNCTION()
	void updateScore(int index);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int playerScore;
	UFUNCTION(BlueprintCallable)
	void build();


};
