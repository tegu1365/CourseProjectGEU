// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlateTrigger.h"
#include "BigDamagePlateTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ABigDamagePlateTrigger : public ABasePlateTrigger
{
	GENERATED_BODY()
protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	virtual void ActionEnd(AActor* ActorInRange) override;

	void DamageActor();

	UPROPERTY()
	AActor* Target;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 40.0f;
};
