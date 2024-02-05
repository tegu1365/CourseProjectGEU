// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "ConeProjectile.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AConeProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AConeProjectile();

protected:
    virtual void BeginPlay() override;
    FTimerHandle DestroyTimerHandle;

    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //UFUNCTION()
    //void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


    UPROPERTY(EditDefaultsOnly)
    class UStaticMeshComponent* Cone;

    UPROPERTY(EditDefaultsOnly)
    float Length;

    UPROPERTY(EditDefaultsOnly)
    float Radius;

    UPROPERTY(EditDefaultsOnly)
    float Damage;

    UPROPERTY(EditDefaultsOnly)
    float Duration;

    void StopPlayerMovement(ACharacter* PlayerCharacter);
    void DestroyCone();

};
