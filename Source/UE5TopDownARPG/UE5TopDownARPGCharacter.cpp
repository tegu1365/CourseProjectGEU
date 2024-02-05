// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Abilities/BaseAbility.h"
#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPG.h"
#include "UI/HealthbarWidget.h"
#include "UI/SoulsWidget.h"
#include "Net/UnrealNetwork.h"

AUE5TopDownARPGCharacter::AUE5TopDownARPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetCastShadow(false);
	WidgetComponent->SetReceivesDecals(false);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->SetupAttachment(RootComponent);

	WidgetSoulsComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetSoulsComponent"));
	WidgetSoulsComponent->SetCastShadow(false);
	WidgetSoulsComponent->SetReceivesDecals(false);
	WidgetSoulsComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetSoulsComponent->SetupAttachment(RootComponent);

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OnTakeAnyDamage.AddDynamic(this, &AUE5TopDownARPGCharacter::TakeAnyDamage);
}

void AUE5TopDownARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(WidgetSoulsComponent->GetWidgetClass()))
	{
		WidgetSoulsComponent->InitWidget();
		SoulsWidget = Cast<USoulsWidget>(WidgetSoulsComponent->GetUserWidgetObject());
	}

	if (IsValid(WidgetComponent->GetWidgetClass()))
	{
		WidgetComponent->InitWidget();
		HealthbarWidget = Cast<UHealthbarWidget>(WidgetComponent->GetUserWidgetObject());
	}
}

void AUE5TopDownARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilityTemplates[0] != nullptr)
	{
		AbilityInstance = NewObject<UBaseAbility>(this, AbilityTemplates[0]);
	}
	if (AbilityHealTemplate != nullptr)
	{
		AbilityHealInstance = NewObject<UBaseAbility>(this, AbilityHealTemplate);
	}

	if (IsValid(HealthbarWidget))
	{
		float HealthPercent = Health / MaxHealth;
		HealthbarWidget->SetPercent(HealthPercent);
	}
}

void AUE5TopDownARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AUE5TopDownARPGCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUE5TopDownARPGCharacter, Health);
	DOREPLIFETIME(AUE5TopDownARPGCharacter, MaxHealth);
}

bool AUE5TopDownARPGCharacter::ActivateAbility(FVector Location)
{
	if (IsValid(AbilityInstance))
	{
		return AbilityInstance->Activate(Location);
	}
	return false;
}

bool AUE5TopDownARPGCharacter::ActivateAbilityHeal(FVector Location)
{
	if (IsValid(AbilityHealInstance))
	{
		return AbilityHealInstance->Activate(Location);
	}
	return false;
}

bool AUE5TopDownARPGCharacter::SetAbilityInstance(int abilityNumber)
{
	AbilityInstance = NewObject<UBaseAbility>(this, AbilityTemplates[abilityNumber]);
	return false;
}

void AUE5TopDownARPGCharacter::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	Health -= Damage;
	OnRep_SetHealth(Health + Damage);
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Health %f"), Health);
	if (IsValid(HealthbarWidget))
	{
		float HealthPercent = Health / MaxHealth;
		HealthbarWidget->SetPercent(HealthPercent);
	}
	if (Health <= 0.0f)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (TimerManager.IsTimerActive(DeathHandle) == false)
		{
			GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AUE5TopDownARPGCharacter::Death, DeathDelay);
		}
	}
}

void AUE5TopDownARPGCharacter::OnRep_SetHealth(float OldHealth)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health %f"), Health));
	}
}

void AUE5TopDownARPGCharacter::Death()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death"));
	AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		GameMode->EndGame(false);
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	if (FMath::RandBool())
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor(AfterDeathSpawnClass, &Location, &Rotation, SpawnParameters);
	}

	GetWorld()->GetTimerManager().ClearTimer(DeathHandle);
	AUE5TopDownARPGPlayerController* PlayerController = Cast<AUE5TopDownARPGPlayerController>(GetController());
	if (IsValid(PlayerController))
	{
		PlayerController->OnPlayerDied();
	}
	Destroy();
}


void AUE5TopDownARPGCharacter::GainSouls(int SoulsGranted)
{ 
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Souls Before %f After %f"), Souls, Souls+SoulsGranted);
	Souls += SoulsGranted;

	if (Souls < 0) Souls = 0;

	if (IsValid(SoulsWidget))
	{
		SoulsWidget->SetSouls(Souls);
	}
}

