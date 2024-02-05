// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulPickup.h"
#include "../UE5TopDownARPGCharacter.h"



void ASoulPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Character->GainSouls(SoulsGranted);
}
