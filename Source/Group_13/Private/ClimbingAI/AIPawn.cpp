// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "Components/ArrowComponent.h"
#include "HealthComp/HealthComponent.h"


// Sets default values
AAIPawn::AAIPawn()
{	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	_Health->OnDamaged.AddUniqueDynamic(this,&AAIPawn::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AAIPawn::Handle_HealthDead);

	
}

void AAIPawn::DropDecal()
{
	UWorld* const world = GetWorld();
	if(world == nullptr || _BloodSplatter == nullptr){ return;}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	//spawnParams.Instigator = GetInstigator();
	//spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	world->SpawnActor(_BloodSplatter, &_DecalLocation->GetComponentTransform(), spawnParams);
}

void AAIPawn::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp,Display,TEXT("dmg"));
	DropDecal();
}

void AAIPawn::Handle_HealthDead(AController* causer)
{
	Destroy();
}


