// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiSpawner.generated.h"



class UArrowComponent;
class AAIPawn;
class UHealthComponent;

UCLASS(Abstract)
class GROUP_13_API AAiSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAiSpawner();

	//scuffed as fuck way of setting up the ai pawn controller, im so sorry :')
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SettupBug();

	void SpawnBug();

	//void SpawnBug_Implementation();

protected:

#pragma region Components

	//order the components with the highest being the most likely to be adjusted by a designer for convenience.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> _AiClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AAIPawn> _AIReference;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> _BugArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxBugs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float currentBugs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelay;
	
	FTimerHandle SpawnBugTimer;

	//these are all in the side view so ordering is not as important
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

#pragma endregion
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_PawnDead();

	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};
