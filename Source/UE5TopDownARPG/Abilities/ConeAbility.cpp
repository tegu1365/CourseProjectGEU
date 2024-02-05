// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeAbility.h"
#include "../Projectiles/ConeProjectile.h"
#include "../UE5TopDownARPG.h"



bool UConeAbility::Activate(FVector Location)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("AbilityCone"));

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

	FVector BeamSpawnLocation = Owner->GetActorLocation() + Direction * 100.0f;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Beam = GetWorld()->SpawnActor<AActor>(BeamClass, BeamSpawnLocation, Direction.Rotation(), SpawnParameters);
	if (IsValid(Beam) == false)
	{
		return false;
	}

	return false;
};
