// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project02_BeSGameModeBase.h"

void AProject02_BeSGameModeBase::StartPlay()
{
	Super::StartPlay();

	spawnA = FVector(-2273.0, -3413.0, 0.0);
	spawnB = FVector(-1800.0, -3413.0, 0.0);
	spawnC = FVector(-600.0, -3413.0, 0.0);
	spawnRotation = FRotator(0, 1, 0);
	enemiesAlive = 0;

	targetScore = 0;
	playerScore = 0;
	spawn(1);
	
	
}
void AProject02_BeSGameModeBase::updateScore() {
	playerScore++;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), playerScore ));
	if (playerScore == 1) {
		spawnWave(1, 2); 
		
	}
	else if (playerScore == 3) {
		spawn(2);
		
	}
	else if (playerScore == 5) {
		spawnWave(2, 2);
	}
	else if (playerScore == 9) {
		spawnWave(1, 5);
		targetScore = playerScore + 5;
	}
	else if (playerScore == targetScore) {
		int count = FMath::Rand() % 3 + 1;
		int waves = FMath::Rand() % 5 + 1;
		targetScore += (count * waves);
		spawnWave(count, waves);
	}
	
}
void AProject02_BeSGameModeBase::spawnWave(int count,int waves) {
	if (waves == 0) return;
	spawn(count);
	waves--;
	
	if(waves){
		FTimerDelegate del;
		del.BindUFunction(this, FName("spawnWave"), count, waves);
		GetWorld()->GetTimerManager().SetTimer(waveHandle, del, 3, false);
	}
	else {
		GetWorldTimerManager().ClearTimer(waveHandle);
	}


}

void AProject02_BeSGameModeBase::spawn(int count) {
	if (count > 3) count = 3; //dont allow more than 3 since only 3 spawns
	if (enemyBP) {
		
		const FActorSpawnParameters spawnParams;
		if (count == 1) {
			int loc = (FMath::Rand() % 3) + 1;
			if (loc == 1) {
				horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnA, spawnRotation, spawnParams));
			}
			else if (loc == 2) {
				horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnB, spawnRotation, spawnParams));
			}
			else {
				horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnC, spawnRotation, spawnParams));
			}
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;

		}
		else if (count == 2) {
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnA, spawnRotation, spawnParams));
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnC, spawnRotation, spawnParams));
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;

			
		}
		else {
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnA, spawnRotation, spawnParams));
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnB, spawnRotation, spawnParams));
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnC, spawnRotation, spawnParams));
			horde[enemiesAlive]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			enemiesAlive++;

		
		}
		
			

	}

}