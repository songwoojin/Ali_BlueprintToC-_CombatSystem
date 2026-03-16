// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AEDamagable.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	DT_None UMETA(DisplayName = "None"),
	DT_Melee UMETA(DisplayName = "Melee"),
	DT_Projectile UMETA(DisplayName = "Projectile"),
	DT_Explosion UMETA(DisplayName = "Explosion"),
	DT_Environment UMETA(DisplayName = "Environment"),
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	DR_None UMETA(DisplayName = "None"),
	DR_HitReaction UMETA(DisplayName = "HitReaction"),
	DR_Stagger UMETA(DisplayName = "Stagger"),
	DR_Stun UMETA(DisplayName = "Stun"),
	DR_KnockBack UMETA(DisplayName = "KnockBack"),
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	float Amount;
	EDamageType  DamageType;
	EDamageResponse DamageResponse;
	bool ShouldDamageInvincible;
	bool CanBeBlocked;
	bool CanBeParried;
	bool ShouldForceInterrupt;
};

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UAEDamagable : public UInterface
{
	GENERATED_BODY()
	
};

/**
 * 
 */
class ALI_YOUTUBE_COMBAT_API IAEDamagable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IAEDamagable();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool IDamagable_TakeDamage(FDamageInfo DamageInfo);
	
protected:
	//필요한 것들인가?
	//float Health;
	//float MaxHealth;
	//float NewHealth;
	//bool WasDamaged;
	
};
