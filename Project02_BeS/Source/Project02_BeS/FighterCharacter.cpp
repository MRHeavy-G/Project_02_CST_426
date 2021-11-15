// Fill out our copyright notice in the Description page of Project Settings.


#include "FighterCharacter.h"

// Sets default values
AFighterCharacter::AFighterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bDead = false;
	canTakeDamage = true;
	health = 200.0f;
	punching = false;
	punchCombo = 0;
	walking = false;
}


// Called when the game starts or when spawned
void AFighterCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AFighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFighterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward",this, &AFighterCharacter::MoveForward);

	PlayerInputComponent->BindAction("Punch",IE_Pressed,this,&AFighterCharacter::Punch);

	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AFighterCharacter::upCombo);
	PlayerInputComponent->BindAction("MOVING", IE_Released, this, &AFighterCharacter::setWalkState);
}
void AFighterCharacter::setWalkState() {
	walking = false;
}
void AFighterCharacter::MoveForward(float Axis)
{
	
	if (!bDead &&Axis ) {
		walking = true;
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);

	}

}

void AFighterCharacter::MoveRight(float Axis)
{
	
	if (!bDead &&Axis) {

		walking = true;
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);

	}

}

void AFighterCharacter::takeDamage(float damage) {

	if (canTakeDamage) {
		canTakeDamage = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Damage Taken"));
		health -= damage;
		GetWorld()->GetTimerManager().SetTimer(DamageDelayHandle, this, &AFighterCharacter::resetDamage, .25, false);
	}
	if (health <= 0)
		bDead = true;
	if (bDead) handleDeath();
}
void AFighterCharacter::handleDeath() {

}
void AFighterCharacter::resetDamage() {
	canTakeDamage = true;
	GetWorldTimerManager().ClearTimer(DamageDelayHandle);
}
void AFighterCharacter::Punch() {
	if (!punching) {
		punching = true;

		GetWorld()->GetTimerManager().SetTimer(PunchDelayHandle, this, &AFighterCharacter::resetPunch, .50, false);
	}
}
void AFighterCharacter::upCombo() {
	if(punching)punchCombo++;
}
void AFighterCharacter::resetPunch() {
	punching = false;
	punchCombo = 0;
	GetWorldTimerManager().ClearTimer(PunchDelayHandle);
}