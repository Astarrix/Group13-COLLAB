// Fill out your copyright notice in the Description page of Project Settings.


#include "AiSpawner.h"

#include "AIPawn.h"


// Sets default values
AAiSpawner::AAiSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAiSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAiSpawner::SpawnBug()
{
	UWorld* const world = GetWorld();
	if(world == nullptr || _AiClass == nullptr) {return;}

	FActorSpawnParameters spawnParams;
	//world->SpawnActor(_AiClass, )
}

void AAiSpawner::Handle_HealthDamaged(float current, float max, float change)
{
}

void AAiSpawner::Handle_HealthDead(AController* causer)
{
	Destroy();
}



