// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "HealAbility.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UHealAbility : public UBaseAbility
{
	GENERATED_BODY()
public:
	virtual bool Activate(FVector Location) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float HealAmount = 40.0f;
};
