#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AOEAttack.generated.h"


UCLASS()
class UE5TOPDOWNARPG_API AAOEAttack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAOEAttack();
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void ActionStart(AActor* ActorInRange);
	virtual void ActionEnd(AActor* ActorInRange);

	void DamageTick();


	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	float DamageOverTimeTick = 0.2f;
	FTimerHandle DamageOverTimeTickTimeHandler;

	UPROPERTY(EditDefaultsOnly)
	float DamagePerTick = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float Radius = 150.0f;

	/*UPROPERTY()
	AActor* Target;*/

	UPROPERTY()
	TArray<AActor*> Targets;

};
