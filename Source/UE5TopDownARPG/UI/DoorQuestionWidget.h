// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorQuestionWidget.generated.h"


UCLASS()
class UE5TOPDOWNARPG_API UDoorQuestionWidget: public UUserWidget
{
	GENERATED_BODY()
public:
	void GetQnA(FString q, FString a);

	UFUNCTION(BlueprintCallable, Category = "MyButtonFunction1")
	void OnAnswer();

	UFUNCTION(BlueprintCallable, Category = "MyButtonFunction2")
	void OnQuit();
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* question;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* answerGiven;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* acceptAnswerBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* quitButton;

	FText Answer;
	
};
