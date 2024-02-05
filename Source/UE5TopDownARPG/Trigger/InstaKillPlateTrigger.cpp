// Fill out your copyright notice in the Description page of Project Settings.


#include "InstaKillPlateTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UE5TopDownARPGCharacter.h"
#include "Engine/DamageEvents.h"



void AInstaKillPlateTrigger::ActionStart(AActor* ActorInRange)
{
    Target = ActorInRange;
}

void AInstaKillPlateTrigger::ActionEnd(AActor* ActorInRange)
{
    Target = nullptr;
}

void AInstaKillPlateTrigger::KillActor()
{
    if (Target == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        Target->TakeDamage(200.0, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
    }
    if (IsValid(Target))
    {
        Target->Destroy();
    }
}