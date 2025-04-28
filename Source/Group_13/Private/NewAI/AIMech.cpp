// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMech.h"

#include "Slowable.h"
#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
AAIMech::AAIMech()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_WeakPoint = CreateDefaultSubobject<USphereComponent>(TEXT("WeakPoint"));
	_WeakPoint->SetupAttachment(_Mesh);

	_DetectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionRange"));
	_DetectionRange->SetupAttachment(_Root);
	_DetectionRange->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAIMech::ShootingOverlap);
	_DetectionRange->OnComponentEndOverlap.AddUniqueDynamic(this, &AAIMech::EndShootingOverlap);

	_AIPercepetion = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	_AISenseSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));

	_AIPercepetion->ConfigureSense(*_AISenseSight);
	_AIPercepetion->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AAIMech::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIMech::Shoot()
{
	
}

void AAIMech::ShootingOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Other != nullptr && Other != this && OtherComp != nullptr)
	{
		//v  checks to see if what was overlapped was the player or now via player only interface :)
		if(UKismetSystemLibrary::DoesImplementInterface(Other,USlowable::StaticClass()))
		{
			UWorld* const world = GetWorld();

			world->GetTimerManager().SetTimer(_ShootTimer,this,&AAIMech::Shoot,_ShootDelay,true);
		}
	}	
}

void AAIMech::EndShootingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAIMech::Handle_HealthDamaged_Implementation(float current, float max, float change)
{
	
}

void AAIMech::Handle_HealthDead_Implementation(AController* causer)
{
	Destroy();
}
