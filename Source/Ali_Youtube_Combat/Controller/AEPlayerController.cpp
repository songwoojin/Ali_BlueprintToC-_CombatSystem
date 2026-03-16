// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AEPlayerController.h"
#include "EnhancedInputSubsystems.h" 

AAEPlayerController::AAEPlayerController()
	:AttackAction(nullptr)
{
}

void AAEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			// 우선순위 0, 혹은 필요에 따라 adjust
			for(int32 i = 0; i < MappingContexts.Num(); ++i)
			{
				if (MappingContexts[i])
				{
					Subsystem->AddMappingContext(MappingContexts[i],  i);
				}
			}
		}
	}
}
