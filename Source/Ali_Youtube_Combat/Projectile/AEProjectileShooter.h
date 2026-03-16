// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEProjectileShooter.generated.h"

class AAEProjectileBase;

UCLASS()
class ALI_YOUTUBE_COMBAT_API AAEProjectileShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	AAEProjectileShooter();

protected:
	virtual void BeginPlay() override;
	
	void Shoot();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ShootPoint;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAEProjectileBase> ProjectileTypeClass;

	UPROPERTY(EditAnywhere)
	float Frequency;

	FTimerHandle TimerHandle;
};
