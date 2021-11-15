// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project02_BeSGameModeBase.h"

void AProject02_BeSGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Project2 Gamemode Loaded!"));

	zombieDelegate.BindUFunction(this, "updateScore");
	playerScore = 0;
	spawnHorde();
	
}
void AProject02_BeSGameModeBase::updateScore() {
	playerScore++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Score: %d"),playerScore ));
	
}
void AProject02_BeSGameModeBase::spawnHorde() {

	if (enemyBP) {
		FVector spawnLocation(0, 0, 100);
		FRotator spawnRotation(0, 0, 0);
		const FActorSpawnParameters spawnParams;

		for (int i = 0; i < hordeSize; i++) {
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnLocation, spawnRotation, spawnParams) );
			horde[i]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
			int x = FMath::RandRange(-100, 200);
			int y = FMath::RandRange(-100, 200);
			spawnLocation += FVector(x, y, 0);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned Enemy"));

		}
	}

}