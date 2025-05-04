// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "FloorAIController.generated.h"

class UEnvQuery;
struct FEnvQueryRequest;
struct FEnvQueryResult;
struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS(Abstract)
class GROUP_13_API AFloorAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloorAIController();
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	//UPROPERTY()
	mutable bool chaseOther = false;

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
	void Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus stimulus);

	void Handle_FindWanderTargetResult(TSharedPtr<FEnvQueryResult> result);

	//UBlackboardComponent* _Blackboard;
	//UBehaviorTreeComponent* _BehaviourTree;
	
};
