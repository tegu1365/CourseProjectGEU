// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectiles/BeamProjectile.h"
#include "Components/CapsuleComponent.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABeamProjectile::ABeamProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Cylinder = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CylinderComponent"));
	Cylinder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Cylinder->SetupAttachment(RootComponent);

	Cylinder->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABeamProjectile::OnBeginOverlap); // this can be removed maybe

	Length = 500.0f;
	Radius = 100.0f;
	DamagePerTick = 5.0f;
	DamageOverTimeTick = 1.0f;
	Duration = 5.0f;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		StopPlayerMovement(PlayerCharacter);
	}

}

void ABeamProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ABeamProjectile::DestroyCylinder, Duration, false);
	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ABeamProjectile::ApplyDamageOverTime, DamageOverTimeTick, true);
}

void ABeamProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABeamProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABeamProjectile::ApplyDamageOverTime()
{
	TArray<AActor*> OverlappingActors;
	Cylinder->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor && OverlappingActor != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			UGameplayStatics::ApplyDamage(OverlappingActor, DamagePerTick, nullptr, this, nullptr);
		}
	}
}

void ABeamProjectile::StopPlayerMovement(ACharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->DisableInput(PlayerController);
		}
		FTimerHandle DestryTimer;
		GetWorldTimerManager().SetTimer(DestryTimer, [PlayerController]() {
			if (PlayerController)
			{
				PlayerController->EnableInput(PlayerController);
			}
			}, Duration, false);
	}
}

void ABeamProjectile::DestroyCylinder()
{
	Destroy();
}
