// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEProjectileBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class ALI_YOUTUBE_COMBAT_API AAEProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAEProjectileBase();
	UBoxComponent* GetBoxComponent() const {return BoxCollisionComponent;}
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
);

	void RotateToTarget();
protected:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBoxComponent> BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	float Speed;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	float Gravity;

	UPROPERTY(VisibleAnywhere,Category="ProjectileSettings")
	UNiagaraComponent* TrailNiagaraComponent;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	UNiagaraSystem* ImpactNiagaraSystem;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	AActor* Target;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	bool bIsHoming;

	UPROPERTY(EditAnywhere,Category="ProjectileSettings")
	float DamageAmount;
};
