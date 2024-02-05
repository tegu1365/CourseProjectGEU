// Fill out your copyright notice in the Description page of Project Settings.


#include "HealAbility.h"
#include "GameFramework/Character.h"
#include "../UE5TopDownARPGCharacter.h"


bool UHealAbility::Activate(FVector Location)
{
	if (Super::Activate(Location) == false)
	{
		return false;
	}

	AUE5TopDownARPGCharacter* Owner = Cast<AUE5TopDownARPGCharacter>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return false;
	}

	Owner->Heal(HealAmount);

	return true;
}

