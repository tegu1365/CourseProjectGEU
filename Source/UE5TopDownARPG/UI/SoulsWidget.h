// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoulsWidget.generated.h"


UCLASS()
class UE5TOPDOWNARPG_API USoulsWidget: public UUserWidget
{
	GENERATED_BODY()
	


public:
	void SetSouls(int soulsToSet);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SoulsTextBLock;
	FString Souls;
};
