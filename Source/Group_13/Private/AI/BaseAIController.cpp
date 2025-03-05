// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "Pawnable.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	/*FGenericTeamId TeamID(FGenericTeamId::GetTeamIdentifier(&Other));
	if(TeamID == FGenericTeamId(1))
	{
		return ETeamAttitude::Friendly;
	}
	if(TeamID == FGenericTeamId(2))
	{
		return ETeamAttitude::Hostile;
	}*/
	return ETeamAttitude::Neutral;
}

// Called when the game starts or when spawned
void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();	
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UPawnable::StaticClass()))
	{
		RunBehaviorTree(IPawnable::Execute_GetBehaviourTree(InPawn));
	}
}

