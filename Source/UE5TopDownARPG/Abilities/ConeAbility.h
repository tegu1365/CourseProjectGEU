// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "ConeAbility.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UConeAbility : public UBaseAbility
{
	GENERATED_BODY()
public:
	virtual bool Activate(FVector Location) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AConeProjectile> BeamClass;
};
