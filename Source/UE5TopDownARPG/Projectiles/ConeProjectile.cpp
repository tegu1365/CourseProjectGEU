// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectiles/ConeProjectile.h"
#include "Components/StaticMeshComponent.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AConeProjectile::AConeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Cone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderComponent"));
	Cone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Cone->SetupAttachment(RootComponent);

	Cone->OnComponentBeginOverlap.AddUniqueDynamic(this, &AConeProjectile::OnBeginOverlap); // this can be removed maybe

	Length = 150.0f;
	Radius = 70.0f;
	Damage = 20.0f;
	Duration = 1.0f;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		StopPlayerMovement(PlayerCharacter);
	}

}

void AConeProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AConeProjectile::DestroyCone, Duration, false);
}

void AConeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConeProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> OverlappingActors;
	Cone->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor && OverlappingActor != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			UGameplayStatics::ApplyDamage(OverlappingActor, Damage, nullptr, this, nullptr);
		}
	}
}

void AConeProjectile::StopPlayerMovement(ACharacter* PlayerCharacter)
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

void AConeProjectile::DestroyCone()
{
	Destroy();
}