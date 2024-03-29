// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlateTrigger.h"
#include "DOTPlateTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ADOTPlateTrigger : public ABasePlateTrigger
{
	GENERATED_BODY()

protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	virtual void ActionEnd(AActor* ActorInRange) override;

	void DamageTick();

	UPROPERTY()
	AActor* Target;

	FTimerHandle CustomDamageTickTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float DamageTickRate = 1.0f;
	
};
