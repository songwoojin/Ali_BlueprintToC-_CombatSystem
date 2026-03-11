// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AEPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Controller/AEPlayerController.h"

AAEPlayerCharacter::AAEPlayerCharacter()
{
	DamageAmount = 10.0f;
}

void AAEPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Triggered 이벤트에 바인딩
		if (AAEPlayerController* AEPC = Cast<AAEPlayerController>(GetController()))
		{
			EnhancedInput->BindAction(AEPC->AttackAction, ETriggerEvent::Started, this, &AAEPlayerCharacter::Attack);
			EnhancedInput->BindAction(AEPC->HealAction, ETriggerEvent::Started, this, &AAEPlayerCharacter::InputHeal);
		}
	}
}

void AAEPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAEPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	APlayerController* PC=Cast<APlayerController>(GetController());
	DisableInput(PC);
}

void AAEPlayerCharacter::InputHeal(const FInputActionValue& Value)
{
	Heal_Implementation(10.0f);
}
