// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorQuestionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPG.h"






void UDoorQuestionWidget::GetQnA(FString q, FString a)
{
	question->SetText(FText::FromString(q));
	Answer = FText::FromString(a);
}

void UDoorQuestionWidget::OnAnswer()
{
	if (answerGiven->Text.CompareTo(Answer))
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("The Given Answer is Correct."));
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->EnableInput(PlayerController);

		this->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Level to switch to: %s."),		*lv.ToString());
		UGameplayStatics::OpenLevel(GetWorld(), lv);
		return;
	}
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("The Given Answer is Incorrect."));

	AUE5TopDownARPGCharacter* PlayerCharacter = Cast<AUE5TopDownARPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->GainSouls(-200);

	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetMapName()));

}

void UDoorQuestionWidget::OnQuit()
{
	this->SetVisibility(ESlateVisibility::Collapsed);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->EnableInput(PlayerController);
}
