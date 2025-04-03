// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiSpawner.generated.h"

class AAIPawn;
class UHealthComponent;

UCLASS(Abstract)
class GROUP_13_API AAiSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAiSpawner();

	void SpawnBug();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAIPawn> _AiClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};
