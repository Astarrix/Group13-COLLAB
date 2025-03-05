// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class GROUP_13_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseAIController();

	// virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<UAIPerceptionComponent> _AIPerception;
	// TObjectPtr<UAISenseConfig_Sight> _AISense_Sight;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
};
