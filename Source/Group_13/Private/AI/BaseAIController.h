// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "BaseAIController.generated.h"

class UEnvQuery;
struct FEnvQueryRequest;
struct FEnvQueryResult;
struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS(Abstract)
class GROUP_13_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseAIController();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvQuery> _EQS_FindWanderTarget;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;
	TObjectPtr<UAISenseConfig_Sight> _AISense_Sight;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	void Handle_FindWanderTargetResult(TSharedPtr<FEnvQueryResult> Result);
};
