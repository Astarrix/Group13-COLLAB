// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorAIController.h"

#include "Pawnable.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "EnvironmentQuery/EnvQueryManager.h"
//#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
AFloorAIController::AFloorAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	//_BehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));
	//_Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	_AISense_Sight= CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));
	
	_AISense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	
	_AIPerception->ConfigureSense(*_AISense_Sight);
	_AIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	
	AAIController::SetGenericTeamId(FGenericTeamId(2));

	FEnvQueryRequest EQR_FindWanderTargetRequest = FEnvQueryRequest(_EQS_FindWanderTarget,GetPawn());
	EQR_FindWanderTargetRequest.Execute(EEnvQueryRunMode::RandomBest25Pct,this, &AFloorAIController::Handle_FindWanderTargetResult);
}

ETeamAttitude::Type AFloorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId TeamId(FGenericTeamId::GetTeamIdentifier(&Other));
	if(TeamId == FGenericTeamId(1))
	{
		UE_LOG(LogTemp,Display, TEXT("Found a unfriendly actor"  ));
		chaseOther = true;
		return ETeamAttitude::Hostile;
	}
	if(TeamId == FGenericTeamId(2))
	{
		chaseOther = false;
		return ETeamAttitude::Friendly;
	}
	chaseOther = true;
	return ETeamAttitude::Neutral;
}

// Called when the game starts or when spawned
void AFloorAIController::BeginPlay()
{
	Super::BeginPlay();
	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AFloorAIController::Handle_TargetPerceptionUpdated);
}

void AFloorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp,Display, TEXT("in pawn"));

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UPawnable::StaticClass()))
	{
		RunBehaviorTree(IPawnable::Execute_GetBehaviourTree(InPawn));
		UE_LOG(LogTemp, Display, TEXT("RunBehaviorTree and in pawn"));		
	}
}

void AFloorAIController::Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus stimulus)
{
	switch (stimulus.Type)
	{
	case 0:
		//react
			if(stimulus.WasSuccessfullySensed() && chaseOther)
			{				
				GetBlackboardComponent()->SetValueAsObject("Target", Actor);
			}
			else
			{
				GetBlackboardComponent()->ClearValue("Target");
			}		
		return;
	default:
		return;
	}
}

void AFloorAIController::Handle_FindWanderTargetResult(TSharedPtr<FEnvQueryResult> result)
{
	if(result->IsSuccessful())
	{
		//GetBlackboardComponent()->ClearValue("newPos");
		GetBlackboardComponent()->SetValueAsVector("newPos", result->GetItemAsLocation(0));
		UE_LOG(LogTemp,Display,TEXT("wandering"));
	}
}



