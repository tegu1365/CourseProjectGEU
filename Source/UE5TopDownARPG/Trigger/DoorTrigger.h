// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlateTrigger.h"
#include "DoorTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ADoorTrigger : public ABasePlateTrigger
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int initialPawns = 0;

	int questionNumber;
	bool IsOpen = false;
	
	bool CheckForPawns();


	virtual void ActionStart(AActor* ActorInRange);
private:
	TArray<FString> questions;
	TArray<FString> answers;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> DoorWidgetClass;
	UPROPERTY()
	class UDoorQuestionWidget* DoorWidget;

};
