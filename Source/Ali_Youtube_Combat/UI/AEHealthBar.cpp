// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AEHealthBar.h"
#include "Components/ProgressBar.h"

void UAEHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAEHealthBar::SetHealthPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}
