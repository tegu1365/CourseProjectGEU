// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "SoulPickup.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ASoulPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	int SoulsGranted = 50;
};
