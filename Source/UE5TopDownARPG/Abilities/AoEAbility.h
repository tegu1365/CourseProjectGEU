// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "AoEAbility.generated.h"

/**
 *
 */
UCLASS()
class UE5TOPDOWNARPG_API UAoEAbility : public UBaseAbility
{
	GENERATED_BODY()
public:
	virtual bool Activate(FVector Location) override;
	//void EndAbility();
protected:
	UPROPERTY(EditDefaultsOnly)
	float Duration = 1.0f;
	FTimerHandle DurationTimeHandler;

	UPROPERTY(EditDefaultsOnly)
	bool bIsAroundThePlayer = true;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAOEAttack> AAreaAttackClass;

};
