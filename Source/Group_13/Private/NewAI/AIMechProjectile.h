// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIMechProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GROUP_13_API AAIMechProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIMechProjectile();

protected:
#pragma region Components
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> _Movement;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
#pragma endregion

	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);
};
