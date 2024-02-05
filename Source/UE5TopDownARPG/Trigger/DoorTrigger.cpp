// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTrigger.h"
#include "../UE5TopDownARPG.h"
#include "../UI/DoorQuestionWidget.h"
#include "Kismet/GameplayStatics.h"


void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();

	questions.Add(TEXT("What 5-letter word typed in all capital letters can be read the same upside down?"));
	answers.Add(TEXT("SWIMS"));
	questions.Add(TEXT("The more you take, the more you leave behind. What am I?"));
	answers.Add(TEXT("Footsteps"));
	questions.Add(TEXT("What is more useful when it is broken?"));
	answers.Add(TEXT("Egg"));
	questions.Add(TEXT("Where do you take a sick boat?"));
	answers.Add(TEXT("To the dock-tor"));

	questionNumber = FMath::RandRange(0, questions.Num());
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Question: %d"), questionNumber);



	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(PlayerController))
	{
		DoorWidget = CreateWidget<UDoorQuestionWidget>(PlayerController, DoorWidgetClass);
		if (IsValid(DoorWidget))
		{
			DoorWidget->AddToViewport();
			DoorWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

void ADoorTrigger::ActionStart(AActor* ActorInRange)
{
	if (!CheckForPawns())
	{
		return;
	}

	if (IsValid(DoorWidget))
	{
		DoorWidget->GetQnA(questions[questionNumber], answers[questionNumber]);
		DoorWidget->SetVisibility(ESlateVisibility::Visible);

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->DisableInput(PlayerController);
		}
	}
}

bool ADoorTrigger::CheckForPawns()
{
	int pawns = GetWorld()->GetNumPawns();
	if (pawns == initialPawns)
		return true;
	
	return false;
}

