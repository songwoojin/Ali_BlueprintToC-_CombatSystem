// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AEBaseCharacter.h"
#include "AEEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ALI_YOUTUBE_COMBAT_API AAEEnemyCharacter : public AAEBaseCharacter
{
	GENERATED_BODY()

public:
	AAEEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Attack() override;
	
protected:
	FTimerHandle AttackTimerHandle;
	
	
};
