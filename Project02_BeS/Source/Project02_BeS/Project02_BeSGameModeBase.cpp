// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project02_BeSGameModeBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"
void AProject02_BeSGameModeBase::StartPlay()
{
	Super::StartPlay();

	
}
void AProject02_BeSGameModeBase::build() {
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	locaA = FVector(-500.0, -640.0, 100.0);
	locaB = FVector(0.0, -640.0, 100.0);
	locaC = FVector(500.0, -640.0, 100.0);
	spawnOutLoc = FVector(0, 0, -1000);
	spawnRotation = FRotator(0, 1, 0);
	enemiesAlive = 0;

	targetScore = 0;
	playerScore = 0;
	if (enemyBP) {
		//Create 20 Zombies
		for (int i = 0; i < 20; i++) {
			horde.Push(GetWorld()->SpawnActor<AEnemyFighterCharacter>(enemyBP, spawnOutLoc, spawnRotation, spawnParams));
			horde[i]->bDead = true;
			horde[i]->setIndex(i);
			horde[i]->OnDeath.AddDynamic(this, &AProject02_BeSGameModeBase::updateScore);
		}
	}
	spawnWave(1, 1);
	targetScore = 1;

}
void AProject02_BeSGameModeBase::updateScore(int index) {
	playerScore++;

	spawnOut(index);
	//reset horde index
	if (playerScore == targetScore) enemiesAlive = 0;
	if (playerScore == 1) {
		spawnIn(locaA);
		spawnIn(locaC);
		targetScore += 2;
	
	}
	else if (playerScore == 3) {
		spawnWave(1, 3);
		targetScore += 3;
	}
	else if(playerScore == targetScore) {
		int count = FMath::Rand() % 4 + 1;
		int waves = FMath::Rand() % 5 + 1;
		spawnWave(count, waves);
		targetScore += (count * waves);
	}

	
}
void AProject02_BeSGameModeBase::spawnWave(int count, int waves) {
	if (waves == 0) {
		GetWorldTimerManager().ClearTimer(waveHandle);
		return;
	}
	for (int i = 0; i < count; i++) {
		int loc = FMath::Rand() % 3 + 1;
		if (loc == 1) spawnIn(locaA);
		if (loc == 2) spawnIn(locaB);
		if (loc == 3) spawnIn(locaC);
	}
	waves--;
	
	if(waves){
		FTimerDelegate del;
		del.BindUFunction(this, FName("spawnWave"), count, waves);
		GetWorld()->GetTimerManager().SetTimer(waveHandle, del, 3, false);
	}



}
void AProject02_BeSGameModeBase::print() {
	for (int i = 0; i < 20; i++) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("HORD[ %d ]: %s"), i, horde[i]->bDead?TEXT("dead"):TEXT("alive")));
	}
}

void AProject02_BeSGameModeBase::spawnIn(FVector newLocation) {
	if (enemiesAlive < 0 || enemiesAlive > 19) return;
	newLocation.X += FMath::Rand() % 100;
	newLocation.X -= FMath::Rand() % 100;
	newLocation.Y += FMath::Rand() % 100;
	newLocation.Y -= FMath::Rand() % 100;
	horde[enemiesAlive]->SetActorLocationAndRotation(newLocation, spawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	horde[enemiesAlive]->bDead = false;
	enemiesAlive++;

}
void AProject02_BeSGameModeBase::spawnOut(int index) {
	if (index < 0 || index > 19) return;
	horde[index]->SetActorLocationAndRotation(spawnOutLoc, spawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	horde[index]->resetHealth();
	horde[index]->bDead = true;
	

}