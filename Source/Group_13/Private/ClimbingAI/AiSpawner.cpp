// Fill out your copyright notice in the Description page of Project Settings.


#include "AiSpawner.h"

#include "AIPawn.h"
#include "Components/ArrowComponent.h"
#include "HealthComp/HealthComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAiSpawner::AAiSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//components
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_SpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Lcoation"));
	_SpawnLocation->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));	
}

void AAiSpawner::SpawnBug()
{
	UWorld* const world = GetWorld();
	if(world == nullptr || _AiClass == nullptr) {return;}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();

	//if(_BugArray.Num()>= maxBugs )
	
	//world->SpawnActor(_AiClass, &_SpawnLocation->GetComponentTransform(), spawnParams);
	
	UE_LOG(LogTemp,Display,TEXT("spawn bug"));

	world->SpawnActor(_AiClass, &_SpawnLocation->GetComponentTransform(), spawnParams);
	
	
	//UGameplayStatics::GetAllActorsOfClass(world,AAIPawn::StaticClass(),_BugArray);

	SettupBug();
}

void AAiSpawner::SettupBug_Implementation()
{
	
}

// Called when the game starts or when spawned
void AAiSpawner::BeginPlay()
{
	Super::BeginPlay();

	//SpawnBug();
	
	_Health->OnDamaged.AddUniqueDynamic(this,&AAiSpawner::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AAiSpawner::Handle_HealthDead);

	UE_LOG(LogTemp,Display,TEXT("begin timer"));
	GetWorld()->GetTimerManager().SetTimer(SpawnBugTimer,this,&AAiSpawner::SpawnBug,SpawnDelay, true);
	
	
}

//void AAiSpawner::SpawnBug()
//{
	
//}

void AAiSpawner::Handle_HealthDamaged(float current, float max, float change)
{
}

void AAiSpawner::Handle_HealthDead(AController* causer)
{
	Destroy();
}



