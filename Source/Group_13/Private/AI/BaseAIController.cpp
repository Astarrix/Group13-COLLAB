// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "Pawnable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
ABaseAIController::ABaseAIController()
{
	//PrimaryActorTick.bCanEverTick = true;

	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	_AISense_Sight= CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));
	
	_AISense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	
	_AIPerception->ConfigureSense(*_AISense_Sight);
	_AIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	
	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId TeamId(FGenericTeamId::GetTeamIdentifier(&Other));
	if(TeamId == FGenericTeamId(1))
	{
		return ETeamAttitude::Friendly;
	}
	if(TeamId == FGenericTeamId(2))
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Neutral;
}

// Called when the game starts or when spawned
void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::Handle_TargetPerceptionUpdated);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UPawnable::StaticClass()))
	{
		RunBehaviorTree(IPawnable::Execute_GetBehaviourTree(InPawn));
	}
}

void ABaseAIController::Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
	case 0:
		//react
			if(Stimulus.WasSuccessfullySensed())
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

void ABaseAIController::Handle_FindWanderTargetResult(TSharedPtr<FEnvQueryResult> Result)
{
	if(Result->IsSuccessful())
	{
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", Result->GetItemAsLocation(0));
		UE_LOG(LogTemp,Display,TEXT("wandering"));
	}
}



