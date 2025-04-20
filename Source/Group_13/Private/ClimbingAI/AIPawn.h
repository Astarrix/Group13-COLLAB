// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDeadSignature);

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
	TSubclassOf<AActor> _BloodSplatter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DecalDelay;
	
	FTimerHandle DecalSpawnTimer;

	//these are all in the side view so ordering is not as important
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _StoppingDistance;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _DecalLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _ForwardArrow;

	
	
#pragma endregion 

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BugSpawned();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DropDecal();

	//collision functions
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	//health 
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};
