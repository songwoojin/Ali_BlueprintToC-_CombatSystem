// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AEDamagable.h"
#include "AEDamageSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlocked,bool,CanBeBlocked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageResponse,FDamageInfo,DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged,float,CurrentHealth,float,MaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALI_YOUTUBE_COMBAT_API UAEDamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAEDamageSystem();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetHealth() const {return Health;}
	float GetMaxHealth() const {return MaxHealth;}
	void Heal(float Amount);
	bool TakeDamage(FDamageInfo InDamageInfo);

public:
	FOnDeath OnDeath;
	FOnBlocked OnBlocked;
	FOnDamageResponse OnDamageResponse;
	FOnHealthChanged OnHealthChanged;
protected:
	float Health;
	float MaxHealth;
	bool IsInvincible;
	bool IsDead;
	bool IsInterruptible;
	bool IsBlocking;
	FDamageInfo DamageInfo;
};
