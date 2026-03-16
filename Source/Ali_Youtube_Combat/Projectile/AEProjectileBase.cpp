// Fill out your copyright notice in the Description page of Project Settings.


#include "AEProjectileBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/AEBaseCharacter.h"

AAEProjectileBase::AAEProjectileBase()
	:Speed(500.0f)
	,Gravity(0.0f)
	,Target(nullptr)
	,bIsHoming(false)
	,DamageAmount(10.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent=BoxCollisionComponent;
	
	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	TrailNiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailNiagaraComponent"));
	TrailNiagaraComponent->SetupAttachment(RootComponent);
	
}

void AAEProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionComponent->OnComponentHit.AddDynamic(this,&AAEProjectileBase::OnHit);
	BoxCollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
	
	if (Target)
	{
		RotateToTarget();
	}
}

void AAEProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ProjectileMovement->InitialSpeed=Speed;
	ProjectileMovement->MaxSpeed=Speed;
	ProjectileMovement->ProjectileGravityScale=Gravity;
	if (bIsHoming)
	{
		ProjectileMovement->bIsHomingProjectile=true;
		ProjectileMovement->HomingTargetComponent=Target->GetRootComponent();
		ProjectileMovement->HomingAccelerationMagnitude=2000.0f;
	}
}

void AAEProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	if (GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *GetOwner()->GetName());
	}
	*/
	
	if (OtherActor == GetOwner())
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	GetWorld(),
	ImpactNiagaraSystem,
	Hit.ImpactPoint,
	Hit.ImpactNormal.Rotation()
	);
	
	// 충돌한 액터 정보
	AAEBaseCharacter* HitActor = Cast<AAEBaseCharacter>(OtherActor);
	if (HitActor)
	{
		FDamageInfo DamageInfo;
		DamageInfo.Amount=DamageAmount;
		DamageInfo.DamageType=EDamageType::DT_Projectile;
		DamageInfo.DamageResponse = EDamageResponse::DR_HitReaction;

		//
		if (HitActor->GetClass()->ImplementsInterface(UAEDamagable::StaticClass()))
		{
			bool bDamaged = IAEDamagable::Execute_IDamagable_TakeDamage(HitActor, DamageInfo);
			if (bDamaged)
			{
				
			}
		}
	}
	
	Destroy();
}

void AAEProjectileBase::RotateToTarget()
{
	FVector ProjectileLocation = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector TargetDirection = (TargetLocation - ProjectileLocation).GetSafeNormal();

	ProjectileMovement->Velocity=TargetDirection*Speed;
}

