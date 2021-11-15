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
	UPROPERTY(EditAnywhere, category = ThingsToSpawn)
		TSubclassOf<class AEnemyFighterCharacter> enemyBP;

	TArray<AEnemyFighterCharacter*> horde;
	void spawnHorde();
	UPROPERTY(VisibleAnywhere)
	int playerScore;
	FScriptDelegate zombieDelegate;
	UFUNCTION()
	void updateScore();

protected:
	UPROPERTY(EditAnywhere, category = Horde)
		int hordeSize =1;
};
