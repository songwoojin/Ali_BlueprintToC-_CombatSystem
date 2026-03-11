// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AEBaseCharacter.h"
#include "Component/AEDamageSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/AEHealthBar.h"

AAEBaseCharacter::AAEBaseCharacter()
	:DamageAmount(10.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	DamageSystem = CreateDefaultSubobject<UAEDamageSystem>(TEXT("DamageSystem"));

	HPBarWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidgetComponent->SetupAttachment(GetMesh());
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetRelativeLocation(FVector(0,0,200));
	HPBarWidgetComponent->SetDrawSize(FVector2D(200.0f,20.0f));
	//HPBarWidgetComponent->SetWidgetClass(HPBarWidgetClass);
}

void AAEBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	DamageSystem->OnDeath.AddDynamic(this,&AAEBaseCharacter::OnDeath);
	DamageSystem->OnBlocked.AddDynamic(this,&AAEBaseCharacter::OnBlocked);
	DamageSystem->OnDamageResponse.AddDynamic(this,&AAEBaseCharacter::OnDamageResponse);
	DamageSystem->OnHealthChanged.AddDynamic(this,&AAEBaseCharacter::OnUpdateHealthBar);

	HealthBarWidget = CreateWidget<UAEHealthBar>(GetWorld(), HPBarWidgetClass);
	HPBarWidgetComponent->SetWidget(HealthBarWidget);

	//Create Widget을 해줄필요가 없음(SetWidgetClass 에서 이미 생성됨)
	//HealthBarWidget = Cast<UAEHealthBar>(HPBarWidgetComponent->GetUserWidgetObject());
	OnUpdateHealthBar(GetCurrentHealth_Implementation(),GetMaxHealth_Implementation());
}

void AAEBaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

float AAEBaseCharacter::GetCurrentHealth_Implementation()
{
	float Health = DamageSystem->GetHealth();
	
	return Health;
}

float AAEBaseCharacter::GetMaxHealth_Implementation()
{
	float MaxHealth = DamageSystem->GetMaxHealth();
	
	return MaxHealth;
}

void AAEBaseCharacter::Heal_Implementation(float Amount)
{
	//float NewHealth =
	DamageSystem->Heal(Amount);
	//return NewHealth;
}

bool AAEBaseCharacter::IDamagable_TakeDamage_Implementation(FDamageInfo DamageInfo)
{
	bool WasDamaged = DamageSystem->TakeDamage(DamageInfo);

	return WasDamaged;
}

void AAEBaseCharacter::OnDeath()
{
	UE_LOG(LogTemp,Warning,TEXT("AAEBaseCharacter::OnDeath"));

	// Capsule 충돌 끄기
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	USkeletalMeshComponent* CharMesh = GetMesh();
	if (IsValid(CharMesh))
	{
		CharMesh->SetSimulatePhysics(true);
		CharMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);	
	}
}

void AAEBaseCharacter::OnBlocked(bool IsBlocked)
{
	if (IsBlocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blocked"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Blocked"));
	}
}

void AAEBaseCharacter::OnDamageResponse(FDamageInfo InDamageInfo)
{
	FString EnumString = UEnum::GetValueAsString(InDamageInfo.DamageResponse);
	UE_LOG(LogTemp,Log,TEXT("Enum Damage Response : %s"),*EnumString);
}

void AAEBaseCharacter::OnUpdateHealthBar(float CurrentHealthBar, float MaxHealth)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(GetCurrentHealth_Implementation()/GetMaxHealth_Implementation());
	}
}

void AAEBaseCharacter::CheckForwardSweep()
{
	float SweepDistance = 100.0f;
	
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * SweepDistance;  // 앞 방향으로 거리만큼

	float SphereRadius = 20.f;  // 검사 반지름

	// 쿼리 파라미터 생성
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  // 이 액터(self)를 무시
	
	FHitResult HitResult;
	// Sphere 형상 생성
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);

	// Sweep 실행
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,              // 결과 구조체
		Start,                  // 시작 위치
		End,                    // 끝 위치
		FQuat::Identity,        // 회전 없음
		ECC_Pawn,               // 검사할 채널 (예: Pawn)
		CollisionShape,          // 충돌 형상
		Params
	);

	if (bHit)
	{
		// 충돌한 액터 정보
		AAEBaseCharacter* HitActor = Cast<AAEBaseCharacter>(HitResult.GetActor());
		if (HitActor)
		{
			FDamageInfo DamageInfo;
			DamageInfo.Amount=DamageAmount;
			DamageInfo.DamageType=EDamageType::DT_Melee;
			DamageInfo.DamageResponse = EDamageResponse::DR_HitReaction;

			//
			if (HitActor->GetClass()->ImplementsInterface(UAEDamagable::StaticClass()))
			{
				bool bDamaged = IAEDamagable::Execute_IDamagable_TakeDamage(HitActor, DamageInfo);
				if (bDamaged)
				{
					if (ExplodeParticleSystem) 
					{
						UGameplayStatics::SpawnEmitterAtLocation(
							GetWorld(),
							ExplodeParticleSystem,
							HitResult.Location,      // 스폰 위치
							GetActorRotation(),      // 스폰 회전
							FVector(1.0f)            // 스케일
						);
					}
				}
			}
		}
	}

#if ENABLE_DRAW_DEBUG
	FColor DebugColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), Start, SphereRadius, 12, DebugColor, false, 2.0f);
	DrawDebugSphere(GetWorld(), End, SphereRadius, 12, DebugColor, false, 2.0f);
#endif
}

void AAEBaseCharacter::Attack()
{
	CheckForwardSweep();
}

void AAEBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAEBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

