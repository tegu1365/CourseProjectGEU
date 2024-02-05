// Fill out your copyright notice in the Description page of Project Settings.


#include "AoEAbility.h"
#include "../Projectiles/AOEAttack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"


bool UAoEAbility::Activate(FVector Location)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("AbilityAOE"));
	if (Super::Activate(Location) == false)
	{
		return false;
	}

	AActor* Owner = Cast<AActor>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return false;
	}

	FVector Direction = Location - Owner->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector AreaSpawnLocation;
	if (bIsAroundThePlayer) {
		AreaSpawnLocation = Owner->GetActorLocation();
	}
	else {

		AreaSpawnLocation = Location;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* AreaAttack = GetWorld()->SpawnActor<AActor>(AAreaAttackClass, AreaSpawnLocation, Direction.Rotation(), SpawnParameters);

	if (IsValid(AreaAttack) == false)
	{
		return false;
	}

	AreaAttack->SetLifeSpan(Duration * 1);

	return true;
}

