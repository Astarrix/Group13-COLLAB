// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDeadSignature);

class AAIProjectile;
class USphereComponent;
class UArrowComponent;
class UHealthComponent;

UCLASS(Abstract)
class GROUP_13_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

	UPROPERTY(BlueprintAssignable)
	FPawnDeadSignature OnPawnDead;

protected:

#pragma region Components

	//order the components with the highest being the most likely to be adjusted by a designer for convenience.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> _BloodSplatter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DecalDelay;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AAIProjectile> _ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _ShootDelay;
	
	FTimerHandle DecalSpawnTimer;
	FTimerHandle ShootTimer;

	//these are all in the side view so ordering is not as important
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _StoppingDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _ShootingDistance;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _DecalLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _ForwardArrow;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	TObjectPtr<UArrowComponent> _FacePlayerArrow;
	
#pragma endregion 

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BugSpawned();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UFUNCTION()
	void DropDecal();

	//collision functions
	UFUNCTION()
	void ShootingOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndShootingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//For rotation the mesh to always face player
	FTimerHandle RotatePawn;
	
	UFUNCTION(BlueprintNativeEvent)
	void ControlRotation(AActor* Player);
	
	//health 
	UFUNCTION(BlueprintNativeEvent)
	void Handle_HealthDamaged(float current, float max, float change);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Handle_HealthDead(AController* causer);
};
