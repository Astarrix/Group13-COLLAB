// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMech.h"

#include "AIMechProjectile.h"
#include "Slowable.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
AAIMech::AAIMech()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_SkelMesh->SetupAttachment(_Root);

	_LeftArrow= CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrow"));
	_LeftArrow->SetupAttachment(_Root);
	_RighttArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrow"));
	_RighttArrow->SetupAttachment(_Root);

	_WeakPoint = CreateDefaultSubobject<USphereComponent>(TEXT("WeakPoint"));
	_WeakPoint->SetupAttachment(_SkelMesh);
	_WeakPoint->OnComponentBeginOverlap.AddUniqueDynamic(this,&AAIMech::WeakPointOverlap);

	_DetectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionRange"));
	_DetectionRange->SetupAttachment(_Root);
	_DetectionRange->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAIMech::ShootingOverlap);
	_DetectionRange->OnComponentEndOverlap.AddUniqueDynamic(this, &AAIMech::EndShootingOverlap);

	_AIPercepetion = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	_AISenseSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));

	_AIPercepetion->ConfigureSense(*_AISenseSight);
	_AIPercepetion->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	_AISenseSight->DetectionByAffiliation.bDetectEnemies = true;
	_AISenseSight->DetectionByAffiliation.bDetectFriendlies = false;
	_AISenseSight->DetectionByAffiliation.bDetectNeutrals = true;	
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	IGenericTeamAgentInterface::SetGenericTeamId(_TeamId);
}

ETeamAttitude::Type AAIMech::GetTeamAttitudeTowards(const AActor& Other)
{
	FGenericTeamId TeamId(FGenericTeamId::GetTeamIdentifier(&Other));
	if(TeamId == FGenericTeamId(1))
	{
		UE_LOG(LogTemp,Display,TEXT("found friend"));
		return ETeamAttitude::Friendly;
	}
	if(TeamId==FGenericTeamId(2))
	{
		UE_LOG(LogTemp,Display,TEXT("found player"));
		return ETeamAttitude::Hostile;
	}
	UE_LOG(LogTemp,Display,TEXT("neautral"));
	return ETeamAttitude::Neutral;	
}

// Called when the game starts or when spawned
void AAIMech::BeginPlay()
{
	Super::BeginPlay();
	_AIPercepetion->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIMech::Handle_TargetPerceptionUpdated);
	
	_Health->OnDamaged.AddUniqueDynamic(this,&AAIMech::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this,&AAIMech::Handle_HealthDead);
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
		FVector start = _LeftArrow->GetComponentLocation();
		FVector forwardVector = _LeftArrow->GetForwardVector();
		FVector end = start+(forwardVector * TraceDistance);
		TArray<AActor*> actorsToIgnore;
		actorsToIgnore.Add(this); //if confused by code it is explained in ai pawn

		FHitResult hitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		world->GetTimerManager().ClearTimer(RotateArrow);
		if(UKismetSystemLibrary::LineTraceSingle(world,start,end,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,actorsToIgnore,EDrawDebugTrace::None,hitResult,true, FLinearColor::Red,
		FLinearColor::Green, 5))
		{
			if(UKismetSystemLibrary::DoesImplementInterface(hitResult.GetActor(),USlowable::StaticClass()))
			{
				UE_LOG(LogTemp,Display,TEXT("shooting player"))
				world->SpawnActor(_Projectile,&_LeftArrow->GetComponentTransform(),spawnParams);
				world->SpawnActor(_Projectile,&_RighttArrow->GetComponentTransform(),spawnParams);
				world->GetTimerManager().SetTimer(RotateArrow,this,&AAIMech::ControlArrowRotation,0.01f,true);
			}
			else
			{
				UE_LOG(LogTemp,Display,TEXT("not player "))
				UE_LOG(LogTemp,Warning, TEXT("shoot %s "), *hitResult.GetActor()->GetName());
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
	world->GetTimerManager().PauseTimer(RotateArrow);	
}

void AAIMech::WeakPointOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: convert this to hit type?
	UE_LOG(LogTemp,Display,TEXT("weak point hit box %f"),_weakPointDmg)
	//_Health->CritDmg(this,);
	UGameplayStatics::ApplyDamage(this,_weakPointDmg,nullptr,this,UDamageType::StaticClass());
	//_Health->_CurrentHealth -= _Health->_CurrentHealth - _weakPointDmg;
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
			if(stimulus.WasSuccessfullySensed() )//&& UKismetSystemLibrary::DoesImplementInterface(Actor,USlowable::StaticClass()))
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
	UE_LOG(LogTemp,Display,TEXT("health component called"));
}

void AAIMech::Handle_HealthDead_Implementation(AController* causer)
{
	Destroy();
}
