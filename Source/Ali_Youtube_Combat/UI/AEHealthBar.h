// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AEHealthBar.generated.h"

/**
 * 
 */

class IAEDamagable;
class UProgressBar;
 
UCLASS()
class ALI_YOUTUBE_COMBAT_API UAEHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	void SetHealthPercent(float Percent);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
};
