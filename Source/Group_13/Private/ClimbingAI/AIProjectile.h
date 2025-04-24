// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GROUP_13_API AAIProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIProjectile();

protected:
	// Called when the game starts or when spawned
#pragma region components
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collider;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> _Movement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float _Slowness;
	
#pragma endregion
	
	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

};
