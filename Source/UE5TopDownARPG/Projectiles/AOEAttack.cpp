#include "AOEAttack.h"
#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"

// Sets default values
AAOEAttack::AAOEAttack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SphereComponent->SetSphereRadius(Radius);

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAOEAttack::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AAOEAttack::OnEndOverlap);
}

void AAOEAttack::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapBegin %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionStart(Other);
}

void AAOEAttack::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapEnd %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionEnd(Other);
}

void AAOEAttack::ActionStart(AActor* ActorInRange)
{
	//Target = ActorInRange;
	Targets.Add(ActorInRange);
	if (Targets.Num() == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(DamageOverTimeTickTimeHandler, this, &AAOEAttack::DamageTick, DamageOverTimeTick, true);
	}
}

void AAOEAttack::ActionEnd(AActor* ActorInRange)
{
	uint32 index = Targets.Find(ActorInRange);
	Targets.RemoveAt(index);
	//Target = nullptr;
	if (Targets.Num() == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageOverTimeTickTimeHandler);
	}
}

void AAOEAttack::DamageTick()
{/*
	if (IsValid(Target))
	{
		Target->TakeDamage(DamagePerTick, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	}*/

	for (AActor* target : Targets)
	{
		if (IsValid(target) && target != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			target->TakeDamage(DamagePerTick, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
		}
	}
}

//void AAOEAttack::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


