// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AEBaseCharacter.h"
#include "AEPlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class ALI_YOUTUBE_COMBAT_API AAEPlayerCharacter : public AAEBaseCharacter
{
	GENERATED_BODY()

public:
	AAEPlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
	virtual void OnDeath() override;

	UFUNCTION()
	void InputHeal(const FInputActionValue& Value);
};
