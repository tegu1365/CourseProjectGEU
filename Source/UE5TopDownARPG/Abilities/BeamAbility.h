// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "BeamAbility.generated.h"


/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UBeamAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	virtual bool Activate(FVector Location) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABeamProjectile> BeamClass;

};
