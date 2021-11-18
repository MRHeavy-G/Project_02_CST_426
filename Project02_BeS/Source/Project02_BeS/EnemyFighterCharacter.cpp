// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFighterCharacter.h"


AEnemyFighterCharacter::AEnemyFighterCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = FMath::RandRange(400, 800);
	attack = false;
}

void AEnemyFighterCharacter::enableWalking() {
	walking = true;
}
void AEnemyFighterCharacter::disableWalking() {
	walking = false;
}
void AEnemyFighterCharacter::startAttack() {
	attack = true;
}
void AEnemyFighterCharacter::endAttack() {
	attack = false;
}
void AEnemyFighterCharacter::handleDeath() {
	
	
	OnDeath.Broadcast(index);
}
void AEnemyFighterCharacter::setIndex(int idNum) {
	index = idNum;
}