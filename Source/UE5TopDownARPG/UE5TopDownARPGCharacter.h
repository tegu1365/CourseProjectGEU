// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE5TopDownARPGCharacter.generated.h"

UCLASS(Blueprintable)
class AUE5TopDownARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGCharacter();

	virtual void PostInitializeComponents() override;

	// Called every frame.
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	FORCEINLINE float GetHealth()const { return Health; }

	FORCEINLINE void Heal(float healAmount) { ((Health + healAmount) >= MaxHealth) ? Health = MaxHealth : Health += healAmount; }
	void GainSouls(int SoulsGranted);

	bool ActivateAbility(FVector Location);
	bool ActivateAbilityHeal(FVector Location);
	bool SetAbilityInstance(int abilityNumber);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* WidgetComponent;
	UPROPERTY()
	class UHealthbarWidget* HealthbarWidget;

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* WidgetSoulsComponent;
	UPROPERTY()
	class USoulsWidget* SoulsWidget;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBaseAbility* AbilityInstance;

	UPROPERTY()
	class UBaseAbility* AbilityHealInstance;

	UPROPERTY(EditDefaultsOnly)
	TArray <TSubclassOf<class UBaseAbility>> AbilityTemplates;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBaseAbility> AbilityHealTemplate;

	UPROPERTY(ReplicatedUsing = OnRep_SetHealth, EditDefaultsOnly)
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	int Souls = 0;

	UPROPERTY(Replicated, EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float DeathDelay = 1.0f;

	FTimerHandle DeathHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AfterDeathSpawnClass;

	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_SetHealth(float OldHealth);

	void Death();
};

