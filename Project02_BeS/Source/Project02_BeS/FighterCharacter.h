// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

//#include "Blueprint/UserWidget.h"

#include "FighterCharacter.generated.h"

UCLASS()
class PROJECT02_BES_API AFighterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFighterCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = State)
		bool punching;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = State)
		int punchCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = State)
		bool walking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = State)
		bool bDead;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = Health)
		float health;
	virtual void handleDeath();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Punch();
	void upCombo();
	FTimerHandle PunchDelayHandle;
	FTimerHandle DamageDelayHandle;
	bool canTakeDamage;

	void resetDamage();

	void resetPunch();
	void setWalkState();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
		void takeDamage(float damage);

	void resetHealth();
};
