// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"


// Sets default values
AAIPawn::AAIPawn()
{
	//components
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	_Mesh->SetupAttachment(RootComponent);

	_StoppingDistance = CreateDefaultSubobject<USphereComponent>(TEXT("Stopping Distance"));
	_StoppingDistance->SetupAttachment(RootComponent);

	_DecalLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Point Down"));
	_DecalLocation->SetupAttachment(RootComponent);

	_ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Faces Forward, Don't Rotate"));
	_ForwardArrow->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
}

void AAIPawn::BugSpawned_Implementation()
{
	//controlled in blueprint?
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	_Health->OnDamaged.AddUniqueDynamic(this,&AAIPawn::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AAIPawn::Handle_HealthDead);

	GetWorld()->GetTimerManager().SetTimer(DecalSpawnTimer, this, &AAIPawn::DropDecal, DecalDelay,true);
}

void AAIPawn::DropDecal()
{
	//spawns a blueprint attached decal based on timer
	UWorld* const world = GetWorld();
	if(world == nullptr || _BloodSplatter == nullptr){ return;}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	world->SpawnActor(_BloodSplatter, &_DecalLocation->GetComponentTransform(), spawnParams);
}

void AAIPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//if(OtherActor != nullptr && OtherActor != this)
	//{
		
	//}
}


void AAIPawn::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp,Display,TEXT("dmg"));

}

void AAIPawn::Handle_HealthDead(AController* causer)
{
	Destroy();
}


