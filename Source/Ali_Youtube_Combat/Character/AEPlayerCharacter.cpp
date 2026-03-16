// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AEPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Controller/AEPlayerController.h"
#include "Projectile/AEProjectileBase.h"

AAEPlayerCharacter::AAEPlayerCharacter()
{
	DamageAmount = 10.0f;

	ProjectileScene=CreateDefaultSubobject<USceneComponent>("ProjectileScene");
	ProjectileScene->SetupAttachment(GetMesh());
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
			EnhancedInput->BindAction(AEPC->FireProjectileAction, ETriggerEvent::Started, this, &AAEPlayerCharacter::InputSpawnProjectile);
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

void AAEPlayerCharacter::InputSpawnProjectile(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire Projectile Input"));
	
	if (ProjectilesClass.Num()>0)
	{
		int32 RandIndex=FMath::RandRange(0, ProjectilesClass.Num()-1);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner=this;
		AAEProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AAEProjectileBase>(ProjectilesClass[RandIndex],ProjectileScene->GetComponentLocation(),ProjectileScene->GetComponentRotation(),SpawnParameters);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->GetBoxComponent()->IgnoreActorWhenMoving(this,true);
		}
	}
}
