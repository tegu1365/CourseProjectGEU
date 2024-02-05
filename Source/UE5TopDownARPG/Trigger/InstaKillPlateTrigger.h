// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlateTrigger.h"
#include "InstaKillPlateTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AInstaKillPlateTrigger : public ABasePlateTrigger
{
	GENERATED_BODY()
protected:
	virtual void ActionStart(AActor* ActorInRange) override;
	virtual void ActionEnd(AActor* ActorInRange) override;

	void KillActor();

	UPROPERTY()
	AActor* Target;
};
