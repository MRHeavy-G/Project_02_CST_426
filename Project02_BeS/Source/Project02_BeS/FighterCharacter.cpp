// Fill out our copyright notice in the Description page of Project Settings.


#include "FighterCharacter.h"

// Sets default values
AFighterCharacter::AFighterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bDead = false;
	health = 200.0f;
	punch = 2;//not punching
}


// Called when the game starts or when spawned
void AFighterCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FighterCharacter."));
	
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
	PlayerInputComponent->BindAction("Punch",IE_Released, this, &AFighterCharacter::Punch);

}

void AFighterCharacter::MoveForward(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);

	}
}

void AFighterCharacter::MoveRight(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);

	}
}

void AFighterCharacter::takeDamage(float damage) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Damage Taken"));
	health -= damage;
	if (health <= 0)
		Destroy();
}

void AFighterCharacter::Punch() {
	punch = 3 - punch;
}