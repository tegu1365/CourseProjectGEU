// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulsWidget.h"
#include "../UE5TopDownARPG.h"
#include "Components/TextBlock.h"


void USoulsWidget::SetSouls(int soulsToSet) {
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Souls Gained %d "), soulsToSet);

	Souls = FString::FromInt(soulsToSet);
	SoulsTextBLock->SetText(FText::FromString(Souls));
}

