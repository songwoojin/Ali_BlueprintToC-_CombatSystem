// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/AEProjectileShooter.h"
#include "Projectile/AEProjectileBase.h"

AAEProjectileShooter::AAEProjectileShooter()
	:ProjectileTypeClass(nullptr)
	,Frequency(2.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	ShootPoint=CreateDefaultSubobject<USceneComponent>(TEXT("ShootPoint"));
	ShootPoint->SetupAttachment(StaticMesh);

}

void AAEProjectileShooter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AAEProjectileShooter::Shoot,
		Frequency,
		true);
}

void AAEProjectileShooter::Shoot()
{
	if (!ProjectileTypeClass)	return;
	
	FActorSpawnParameters SpawnParameters;
	
	SpawnParameters.Owner=this;
	AAEProjectileBase* SpawnActor =GetWorld()->SpawnActor<AAEProjectileBase>(ProjectileTypeClass,ShootPoint->GetComponentLocation(),ShootPoint->GetComponentRotation(),SpawnParameters);
	
}


