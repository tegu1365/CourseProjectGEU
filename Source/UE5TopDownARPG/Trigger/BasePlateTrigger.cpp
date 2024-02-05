

#include "BasePlateTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"

// Sets default values
ABasePlateTrigger::ABasePlateTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerPlate = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionPlateTrigger"));
	TriggerPlate->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerPlate->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = TriggerPlate;

	TriggerPlate->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasePlateTrigger::OnBeginOverlap);
	TriggerPlate->OnComponentEndOverlap.AddUniqueDynamic(this, &ABasePlateTrigger::OnEndOverlap);
}

// Called when the game starts or when spawned
void ABasePlateTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlateTrigger::ActionStart(AActor* ActorInRange)
{

}

void ABasePlateTrigger::ActionEnd(AActor* ActorInRange)
{

}

void ABasePlateTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapBegin %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionStart(Other);
}

void ABasePlateTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapEnd %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionEnd(Other);
}

// Called every frame
void ABasePlateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
