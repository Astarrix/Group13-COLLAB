// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

class UHealthComponent;

UCLASS(Abstract)
class GROUP_13_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:

#pragma region Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	
#pragma endregion 
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};
