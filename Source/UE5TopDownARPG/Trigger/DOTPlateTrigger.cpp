// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTPlateTrigger.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DamageEvents.h"


void ADOTPlateTrigger::ActionStart(AActor* ActorInRange)
{
    Target = ActorInRange;

    GetWorld()->GetTimerManager().SetTimer(CustomDamageTickTimerHandle, this, &ADOTPlateTrigger::DamageTick, DamageTickRate, true);
}

void ADOTPlateTrigger::ActionEnd(AActor* ActorInRange)
{
    Target = nullptr;
    GetWorld()->GetTimerManager().ClearTimer(CustomDamageTickTimerHandle);
}

void ADOTPlateTrigger::DamageTick()
{
    APlayerController* PlayerController = Cast<APlayerController>(Target->GetInstigatorController()); // not sure if it works like this
    if (IsValid(Target) && PlayerController)
    {
        Target->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
    }
}