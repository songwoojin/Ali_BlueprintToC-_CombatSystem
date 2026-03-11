// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/AEDamagable.h"
#include "GameFramework/Character.h"
#include "AEBaseCharacter.generated.h"

class UAEDamageSystem;
class UAEHealthBar;

UCLASS()
class ALI_YOUTUBE_COMBAT_API AAEBaseCharacter : public ACharacter, public IAEDamagable
{
	GENERATED_BODY()

public:
	AAEBaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual float GetCurrentHealth_Implementation() override;
	virtual float GetMaxHealth_Implementation() override;
	virtual void Heal_Implementation(float Amount) override;
	virtual bool IDamagable_TakeDamage_Implementation(FDamageInfo DamageInfo) override;

	UFUNCTION()
	virtual void OnDeath();
	UFUNCTION()
	void OnBlocked(bool IsBlocked);
	UFUNCTION()
	void OnDamageResponse(FDamageInfo InDamageInfo);
	UFUNCTION()
	void OnUpdateHealthBar(float CurrentHealthBar,float MaxHealth);

	virtual void CheckForwardSweep();
	virtual void Attack();
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAEDamageSystem> DamageSystem;
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplodeParticleSystem;

	UPROPERTY(EditAnywhere)
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> HPBarWidgetClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="UI")
	class UWidgetComponent* HPBarWidgetComponent;

	UPROPERTY()
	TObjectPtr<UAEHealthBar> HealthBarWidget;
};
