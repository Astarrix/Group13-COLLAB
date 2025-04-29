// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMech.h"

#include "AIMechProjectile.h"
#include "Slowable.h"
#include "Components/ArrowComponent.h"
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

	_ForwardArrow= CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_ForwardArrow->SetupAttachment(_Root);

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

	_AISenseSight->DetectionByAffiliation.bDetectEnemies = true;
	_AISenseSight->DetectionByAffiliation.bDetectFriendlies = true;
	_AISenseSight->DetectionByAffiliation.bDetectNeutrals = true;	
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AAIMech::BeginPlay()
{
	Super::BeginPlay();
	_AIPercepetion->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIMech::Handle_TargetPerceptionUpdated);
}

void AAIMech::Shoot()
{
	if(canSeePlayer)
	{
		UWorld* const world = GetWorld();
		//todo: shoot
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwner();
		
		UE_LOG(LogTemp,Display,TEXT("can see and is shooting"));
		float TraceDistance = _DetectionRange->GetScaledSphereRadius();
		FVector start = _ForwardArrow->GetComponentLocation();
		FVector forwardVector = _ForwardArrow->GetForwardVector();
		FVector end = start+(forwardVector * TraceDistance);
		TArray<AActor*> actorsToIgnore;
		//actorsToIgnore.Add(this); //if confused by code it is explained in ai pawn

		FHitResult hitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if(UKismetSystemLibrary::LineTraceSingle(world,start,end,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,actorsToIgnore,EDrawDebugTrace::ForDuration,hitResult,true, FLinearColor::Red,
		FLinearColor::Green, 5))
		{
			if(UKismetSystemLibrary::DoesImplementInterface(hitResult.GetActor(), USlowable::StaticClass()))
			{
				UE_LOG(LogTemp,Display,TEXT("shooting player"))
				world->SpawnActor(_Projectile,&_ForwardArrow->GetComponentTransform(),spawnParams);
			}
			else
			{
				UE_LOG(LogTemp,Display,TEXT("not player"))
			}

		}
	}
	else
	{
		UE_LOG(LogTemp,Display,TEXT("cant see "));
	}
	
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
			world->GetTimerManager().SetTimer(RotateArrow,this,&AAIMech::ControlArrowRotation,0.01f,true);
		}
	}	
}

void AAIMech::EndShootingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UWorld* const world = GetWorld();
	//world->GetTimerManager().ClearTimer(_ShootTimer);
	world->GetTimerManager().ClearTimer(RotateArrow);	
}

void AAIMech::ControlArrowRotation_Implementation()
{
}

void AAIMech::Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus stimulus)
{
	switch (stimulus.Type)
	{
	case 0:
		//react
			if(stimulus.WasSuccessfullySensed() && UKismetSystemLibrary::DoesImplementInterface(Actor,USlowable::StaticClass()))
			{
				UE_LOG(LogTemp,Display,TEXT("sensed true"));
				_PlayerRef = Actor;
				canSeePlayer = true;
			}
			else
			{
				UE_LOG(LogTemp,Display,TEXT("sensed false"));

				canSeePlayer = false;
			}		
		return;
	default:
		return;
	}
}

void AAIMech::Handle_HealthDamaged_Implementation(float current, float max, float change)
{
	
}

void AAIMech::Handle_HealthDead_Implementation(AController* causer)
{
	Destroy();
}
