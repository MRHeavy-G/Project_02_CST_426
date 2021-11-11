// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFighterCharacter.h"


AEnemyFighterCharacter::AEnemyFighterCharacter() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyFighterCharacter::enableWalking() {
	walking = true;
}
void AEnemyFighterCharacter::disableWalking() {
	walking = false;
}