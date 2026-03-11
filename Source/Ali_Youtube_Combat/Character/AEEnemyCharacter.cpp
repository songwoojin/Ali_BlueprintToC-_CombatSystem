// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AEEnemyCharacter.h"
#include "Blueprint/UserWidget.h"

AAEEnemyCharacter::AAEEnemyCharacter()
{
}

void AAEEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&AAEEnemyCharacter::Attack,
		3.0f,
		true
		);
	
}

void AAEEnemyCharacter::Attack()
{
	Super::Attack();
}
