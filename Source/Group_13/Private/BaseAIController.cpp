// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "Pawnable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ABaseAIController::ABaseAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

