// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FighterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "PlayerFighterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT02_BES_API APlayerFighterCharacter : public AFighterCharacter
{
	GENERATED_BODY()

public:
	APlayerFighterCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
protected:
	virtual void handleDeath();
};
