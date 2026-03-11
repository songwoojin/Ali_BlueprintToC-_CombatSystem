// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AEDamageSystem.h"

UAEDamageSystem::UAEDamageSystem()
	:Health(50.0f)
	,MaxHealth(50.0f)
	,IsInvincible(false)
	,IsDead(false)
	,IsInterruptible(false)
	,IsBlocking(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAEDamageSystem::BeginPlay()
{
	Super::BeginPlay();
}

void UAEDamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAEDamageSystem::Heal(float Amount)
{
	if (!IsDead)
	{
		Health = Health + Amount;
		Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	}

	OnHealthChanged.Broadcast(Health,MaxHealth);
	
	//return Health;
}

bool UAEDamageSystem::TakeDamage(FDamageInfo InDamageInfo)
{
	bool bShouldDamageInvincible = InDamageInfo.ShouldDamageInvincible;
	bool bCanBeBlocked = InDamageInfo.CanBeBlocked;
	bool bShouldForceInterrupt = InDamageInfo.ShouldForceInterrupt;
	bool bCanBeParried = InDamageInfo.CanBeParried;
	
	if ((!IsInvincible || bShouldDamageInvincible) && !IsDead)
	{
		if (bCanBeBlocked && IsBlocking)
		{
			//Block Damage
			if (bCanBeParried)
			{
				OnBlocked.Broadcast(bCanBeParried);
			}
			
			return false;
		}
		else
		{
			//Do Damage
			Health = Health - InDamageInfo.Amount;
			Health = FMath::Clamp(Health, 0.f, MaxHealth);
			OnHealthChanged.Broadcast(Health,MaxHealth);
			if (Health<=0.0f)
			{
				IsDead = true;
				OnDeath.Broadcast();
				UE_LOG(LogTemp,Warning,TEXT("UAEDamageSystem::Kill"));
			}
			else if (bShouldForceInterrupt || IsInterruptible)
			{
				OnDamageResponse.Broadcast(InDamageInfo);
			}

			return true;
		}
	}
	else
	{
		//No Damage
		return false;
	}
	
}


