// Fill out your copyright notice in the Description page of Project Settings.


#include "AIClimbController.h"

#include "../../../../Plugins/SpiderAIPlugin/spider-navigation-plugin-master/Source/SpiderNavigation/Public/SpiderNavigation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAIClimbController::AAIClimbController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAIClimbController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessPawn = InPawn;
	RunBehaviorTree(GetBehaviourTree(InPawn));
	//if wanna do home location do it in pawn?
	//GetBlackboardComponent()->SetValueAsVector("HomeLocation", GetActorLocation());
}

// Called when the game starts or when spawned
void AAIClimbController::BeginPlay()
{	
	Super::BeginPlay();

	if(_SpiderNav)
	{
		FActorSpawnParameters spawnParams;
		_SpiderNavRef = GetWorld()->SpawnActor<ASpiderNavigation>(_SpiderNav, spawnParams);
	}
	
}

// Called every frame
void AAIClimbController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIClimbController::Move(FVector Destination)
{
	AiLocation = PossessPawn->GetActorLocation();
	MoveDesination = _SpiderNavRef->FindClosestNodeLocation(AiLocation);
	CurrentPath = _SpiderNavRef->FindPath(AiLocation,MoveDesination,test);
	CurrentPath.Remove(CurrentPath[0]);
	//update local move
	//|_> if local path found must move = true
}

void AAIClimbController::UpdateRotation()
{
	
}

void AAIClimbController::UpdateLocalMove()
{
	if(CurrentPath.Max()>0)
	{
		
	}
}

