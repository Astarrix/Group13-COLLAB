// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPawn.h"
#include "AIMech.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMechDeadSignature);

UCLASS(Abstract)
class GROUP_13_API AAIMech : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIMech();

protected:

#pragma region Components
	UPROPERTY(EditAnywhere, blueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	//projectile
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _WeakPoint;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _DetectionRange;

#pragma endregion Components
	
	virtual void BeginPlay() override;
};
