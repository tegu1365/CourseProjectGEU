#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BeamProjectile.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API ABeamProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeamProjectile();

protected:

    void ApplyDamageOverTime();

    virtual void BeginPlay() override;
    FTimerHandle DestroyTimerHandle;
    FTimerHandle DamageTimerHandle;

    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //UFUNCTION()
    //void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


    UPROPERTY(EditDefaultsOnly)
    class UCapsuleComponent* Cylinder;

    UPROPERTY(EditDefaultsOnly)
    float Length;

    UPROPERTY(EditDefaultsOnly)
    float Radius;

    UPROPERTY(EditDefaultsOnly)
    float DamagePerTick;

    UPROPERTY(EditDefaultsOnly)
    float DamageOverTimeTick;

    UPROPERTY(EditDefaultsOnly)
    float Duration;

    void StopPlayerMovement(ACharacter* PlayerCharacter);
    void DestroyCylinder();
};
