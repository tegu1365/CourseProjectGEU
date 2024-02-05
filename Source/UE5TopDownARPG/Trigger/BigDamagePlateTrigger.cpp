// Fill out your copyright notice in the Description page of Project Settings.


#include "BigDamagePlateTrigger.h"
#include "Engine/DamageEvents.h"



void ABigDamagePlateTrigger::ActionStart(AActor* ActorInRange)
{
    Target = ActorInRange;
    DamageActor();
}

void ABigDamagePlateTrigger::ActionEnd(AActor* ActorInRange)
{
    Target = nullptr;
}

void ABigDamagePlateTrigger::DamageActor()
{
    APlayerController* PlayerController = Cast<APlayerController>(Target->GetInstigatorController()); // not sure if it works like this
    if (IsValid(Target) && PlayerController)
    {
        Target->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
    }
}